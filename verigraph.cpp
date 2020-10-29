#include <slang/compilation/Compilation.h>
#include <slang/compilation/Definition.h>
#include <slang/symbols/CompilationUnitSymbols.h>
#include <slang/symbols/InstanceSymbols.h>
#include <slang/syntax/SyntaxTree.h>
#include <slang/util/Bag.h>
#include <slang/text/SourceManager.h>

#include <iostream>

using namespace slang;

void printDepsForInstance(InstanceSymbol const& parent) {
    for (auto const& child : parent.body.membersOfType<InstanceSymbol>()) {
        std::cout << "\t\"" << parent.getDefinition().name << "\n" << parent.name << "()\" -> \"" << child.getDefinition().name << "\n" << child.name << "()\"" << std::endl;
        printDepsForInstance(child);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Error: files missing" << std::endl;
        return 1;
    }
    
    std::vector<std::string> files(argv + 1, argv + argc);
    SourceManager sourceManager;
    std::vector<SourceBuffer> buffers;
    for (const std::string& file : files) {
        SourceBuffer buffer = sourceManager.readSource(file);
        if (!buffer) {
            continue;
        }

        buffers.push_back(buffer);
    }

    Bag options;
    Compilation compilation(options);
    compilation.addSyntaxTree(SyntaxTree::fromBuffers(buffers, sourceManager));

    auto topInstances = compilation.getRoot().topInstances;


    std::cout << "digraph dependencies" << std::endl;
    std::cout << "{" << std::endl;
    std::cout << "node [shape=record];" << std::endl;
    if (!topInstances.empty()) {
        for (auto inst : topInstances) {    
            printDepsForInstance(*inst);
        }
    }
    std::cout << "}" << std::endl;
    return 0;
}