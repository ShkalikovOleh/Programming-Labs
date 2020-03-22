#include <algorithm>

#include "InfixToPostfix.h"
#include "Stack.h"

enum CharType
{
    Operator,
    Operand,
    Separator,
    BeginBlock,
    EndBlock
};

CharType getSymbolType(char symbol)
{
    if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/')
        return CharType::Operator;
    else if(symbol >= 'A' && symbol <= 'z') //variables
        return CharType::Operand;
    else if(symbol >= '0' && symbol <= '9') //numbers
        return CharType::Operand;
    else if(symbol == '(' || symbol == '[')
        return CharType::BeginBlock;
    else if(symbol == ')' || symbol == ']')
        return CharType::EndBlock;
    else
        return CharType::Separator;
}

int getOperatorPriority(char operatorSymbol)
{    
    switch (operatorSymbol)
    {
    case '+':
    case '-':
        return 0;        
    case '*':
    case '/':
        return 1;
    }
}

int countByType(const std::string& str, CharType type)
{
    int counter = 0;
    for (auto &&s : str)
    {
        if(getSymbolType(s) == type)
            counter++;
    }
    return counter;
}

template<typename Container>
std::string infixToPostfix(const std::string& infix)
{
    if(countByType(infix, CharType::BeginBlock) != countByType(infix, CharType::EndBlock))
        throw std::exception(); //incorrect bracket structure

    std::string result = "";
    Stack<char, Container> stash;    

    for (auto &&symbol : infix)
    {
        auto type = getSymbolType(symbol);
        switch (type)
        {
        case CharType::Operand:        
            result += symbol;
            break;        
        case CharType::BeginBlock:
            stash.push(symbol);
            break;
        case CharType::EndBlock:         
            while (getSymbolType(stash.top()) != CharType::BeginBlock)
            {
                result += stash.top();
                stash.pop();
            }
            stash.pop();            
            break;
        case CharType::Operator:
        {                        
            int symbolPriority = getOperatorPriority(symbol);
            int topPriority = 0;
            if(!stash.empty())
                topPriority = getOperatorPriority(stash.top());
            
            auto isTopBegin = [&stash](){ return (getSymbolType(stash.top()) == CharType::BeginBlock); };

            while(!stash.empty() && !isTopBegin() && symbolPriority <= topPriority)
            {
                result += stash.top();
                stash.pop();
            }
            stash.push(symbol);
            break;
        }
        default:
            break;
        }
    }

    while (!stash.empty())
    {            
        result += stash.top();
        stash.pop();        
    }
    
    return result;
}