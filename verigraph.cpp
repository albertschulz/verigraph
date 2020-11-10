#include <cli.hpp>
#include <slang/compilation/Compilation.h>
#include <slang/compilation/Definition.h>
#include <slang/symbols/CompilationUnitSymbols.h>
#include <slang/symbols/InstanceSymbols.h>
#include <slang/symbols/MemberSymbols.h>
#include <slang/symbols/CompilationUnitSymbols.h>
#include <slang/symbols/Scope.h>
#include <slang/symbols/BlockSymbols.h>
#include <slang/syntax/SyntaxTree.h>
#include <slang/util/Bag.h>
#include <slang/text/SourceManager.h>
#include <iostream>
#include <sstream>
#include <set>

using namespace slang;

std::string serialize(InstanceSymbol const& symbol) {
    std::stringstream ss;
    ss << "\"" << (symbol.isInterface()? "<interface>\n":"") << symbol.getDefinition().name << "\"";
    return ss.str();
}

void printDepsForScope(std::set<std::string>& list, InstanceSymbol const& parent, Scope const& scope, int levels) {
    if (levels == 0) return;
    for (auto const& block : scope.membersOfType<GenerateBlockSymbol>()) {
        printDepsForScope(list, parent, block, levels);
    }
    for (auto const& block : scope.membersOfType<GenerateBlockArraySymbol>()) {
        printDepsForScope(list, parent, block, levels);
    }
    for (auto const& child : scope.membersOfType<InstanceSymbol>()) {
        std::stringstream ss;
        ss << "\t" << serialize(parent) << " -> " << serialize(child);
        list.insert(ss.str());
        printDepsForScope(list, child, child.body, levels-1);
    }
    for (auto const& child : scope.membersOfType<WildcardImportSymbol>()) {
        std::stringstream ss;
        ss << "\t" << serialize(parent) << " -> " << "\"" << child.packageName << "::*" << "\"";
        list.insert(ss.str());
    }
    for (auto const& child : scope.membersOfType<ExplicitImportSymbol>()) {
        std::stringstream ss;
        ss << "\t" << serialize(parent) << " -> " << "\"" << child.packageName << "::" << child.importName << "\"";
        std::string tmp = ss.str();
        list.insert(tmp);
    }
}

int main(int argc, const char **argv)
{
    cli::Parser parser(argc, argv);
    parser.help() << R"(Awesome CLI tool Usage: <command> [options] filenames...)";

    auto root = parser.option("root").alias("r").description("Root module").getValue();
    auto max_levels = parser.option("max-levels").alias("l").description("Maximum levels. Defaults to -1 (no limit)").defaultValue("-1").getValue();

    parser.defaultCommand().alias("p").execute([&](cli::Parser &parser)
    {
		if (parser.hasErrors())
			return EXIT_FAILURE;

        parser.getRemainingArguments(argc, argv);
        std::vector<std::string> files(argv + 1, argv + argc);
        
        SourceManager sourceManager;
        std::vector<SourceBuffer> buffers;
        for (const std::string& file : files) {
            auto buffer = sourceManager.readSource(file);
            if (!buffer) {
                std::cerr << "Error reading file: " << file << std::endl;
                continue;
            }
            buffers.push_back(buffer);
        }

        Bag options;
        Compilation compilation(options);
        compilation.addSyntaxTree(SyntaxTree::fromBuffers(buffers, sourceManager));
        
        Scope rootScope = compilation.getRoot();
        std::set<std::string> entries;
        for (auto& instance : rootScope.membersOfType<InstanceSymbol>())
            printDepsForScope(entries, instance, instance.body, std::stoi(max_levels));

        std::cout << "digraph dependencies" << std::endl;
        std::cout << "{" << std::endl;
        std::cout << "node [shape=record];" << std::endl;
        std::cout << "node [fontname = \"monospace\"];" << std::endl;
        for (auto const& item : entries)
            std::cout << item << std::endl;
        std::cout << "}" << std::endl;
        
		return EXIT_SUCCESS;
	});

    int result;
	bool executed = parser.executeCommand(result);

    if (parser.hasErrors())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}