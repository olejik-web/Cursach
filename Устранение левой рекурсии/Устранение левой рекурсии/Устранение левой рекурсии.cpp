#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <set>
#include <algorithm>
#include <stack>
#include <memory>
#include <iomanip>
#include <complex>
#define M_PI 3.14159265358979323846
#define BRACKETS_ERROR -1
#define LOG_ERROR -2
#define SQRT_ERROR -3
#define DIVISION_ZERO_ERROR -4

// ВАЖНОЕ
// Компилятор не умеет брать корни из отрицательных чисел, когда они получаются не комплексные
// Ну, пиздец это как бы
// Надо исправлять каким-то образом
// pow(-27, 1.0 / 3.0) --> -nan(ind), а нужно -3
// pow(-8, 1.0 / 3.0) --> -nan(ind), а нужно -2
// pow(-32, 0.2) --> -nan(ind), а нужно -2
// pow(-23, 7.0/15.0) --> -nan(ind), а нужно -4.31989300289223
// "pow(-27.0, 1.0 / 3.0)=" << pow(-27.0, 1.0 / 3.0) << ", а правильный ответ -3\n";
// "pow(-8.0, 1.0 / 3.0)=" << pow(-8.0, 1.0 / 3.0) << ", а правильный ответ -2\n";
// "pow(-32.0, 0.2)=" << pow(-32.0, 0.2) << ", а правильный ответ -2\n";
// "pow(-23.0, 7.0 / 15.0)=" << pow(-23.0, 7.0 / 15.0) << ", а правильный ответ -4.31989300289223\n";
// "pow(-8.0, 5.0 / 3.0)=" << pow(-8.0, 5.0 / 3.0) << ", а правильный ответ -32\n";
// "pow(-32.0, 3.0 / 5.0)=" << pow(-32.0, 3.0 / 5.0) << ", а правильный ответ -8\n";


using namespace std;
map<string, vector<string> > Grammar;
vector<string> Digits = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
vector<string> Variables = {}; // это для преобразования грамматики в ll1. НЕ МАТЕМАТИЧЕСКИЕ ПЕРЕМЕННЫЕ!
vector<string> MathVariables = { "x", "t" };
vector<string> Constants = { "pi" };
vector<string> Terminals = {
"+", "-", "^", "*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
"x", "t", "/", "ln(", "(", ")", "c", "s", "os(", "qrt(",
"in(", "g(", "exp(", "pi" };
vector<string> UsedWords = { "+", "-", "^", "*", "/", "0", "1", "2", "3", "4", "5", "6", "7",
"8", "9", "pi", "x", "t", "cos", "sin", "tg", "ctg", "sqrt", "exp", "ln", "(", ")"
};
vector<string> Operators = { "+", "-", "^", "*", "/", "(", ")" };
vector<string> Functions = { "cos", "sin", "tg", "ctg", "sqrt", "exp", "ln" };
map<string, double> NodesCalculatedValuesMap;
vector<string> NotTerminals = {
"A", "B", "C", "D", "E", "F", "G", "H", "I",
"J", "K", "L", "M", "N", "P", "Q", "T" };
string StartNotTerminal = "E";
map<string, set<string>> FIRST;
map<string, set<string>> FOLLOW;
map<string, map<string, vector<pair<string, vector<string>>>>> SyntaxAnalyseTable;
double xVALUE = -10;
double tVALUE = 10;

enum TokenType
{
    Plus = 0,
    Multiply,
    Minus,
    Division,
    LeftBracket,
    RightBracket,
    Factorization,
    Num
};

class Node
{
public:
    Node(Node* parent, string& value);
    string value() const;
    Node* parent() const;
    Node* child(int inx) const;
    Node* backChild();
    void addChild(string& value);
    void setParent(Node* parent);
    void setValue(string& value);
    void printTree(int level);
    void reverseTree();
    int childsSize();
    // void collectExpression();
    void collectTokens();
    void calcExpression();
    double calcValue();
    string expression();
    void clear();

private:
    string m_value;
    Node* m_parent;
    vector<unique_ptr<Node>> m_childs;
    double m_calcValue{ 0 };
    vector<pair<string, bool>> m_tokens;
    vector<pair<string, bool>> m_postfixTokens;
    string m_expression{ "" };
};

bool isConstant(string& value)
{
    bool flag = false;
    for (auto myConst : Constants)
        flag |= value == myConst;
    return flag;
}

bool isMathVariable(string& value)
{
    bool flag = false;
    for (auto mathVar : MathVariables)
        flag |= value == mathVar;
    return flag;
}

bool isDigit(string& value)
{
    bool flag = false;
    for (auto digit : Digits)
        flag |= value == digit;
    return flag;
}

bool isFunction(string& value)
{
    bool flag = false;
    for (auto function : Functions)
        flag |= value == function;
    return flag;
}

bool isOperator(string& value)
{
    bool flag = false;
    for (auto op : Operators)
        flag |= value == op;
    return flag;
}

void transferToPostfixTokens(vector<pair<string, bool>>& tokens, vector<pair<string, bool>>& postfixTokens)
{
    map<string, int> operatorsPriority =
    { {"(", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3} };
    stack<pair<string, bool>> algoStack;
    int minusCount = 0;
    // for (auto token : tokens)
        // cout << token.first << " ";
    // cout << "\n";
    for (auto token : tokens)
    {
        if (token.first == "(" && token.second)
            minusCount++;
        else if (!isOperator(token.first))
            token.second ^= static_cast<bool>(minusCount % 2);
        if (!isOperator(token.first) && !isFunction(token.first))
            postfixTokens.push_back(token);
        else if (isFunction(token.first))
            algoStack.push(token);
        else if (isOperator(token.first) && token.first != "(" && token.first != ")")
        {
            while (!algoStack.empty()
                && operatorsPriority[algoStack.top().first] >= operatorsPriority[token.first])
            {
                postfixTokens.push_back(algoStack.top());
                algoStack.pop();
            }
            algoStack.push(token);
        }
        else if (token.first == "(")
            algoStack.push(token);
        else if (token.first == ")")
        {
            while (!algoStack.empty() && algoStack.top().first != "(")
            {
                postfixTokens.push_back(algoStack.top());
                algoStack.pop();
            }
            if (algoStack.empty())
            {
                cout << "Error in brackets!";
                exit(BRACKETS_ERROR);
            }
            if (algoStack.top().second)
                minusCount--;
            algoStack.pop();
            if (!algoStack.empty() && isFunction(algoStack.top().first))
            {
                postfixTokens.push_back(algoStack.top());
                algoStack.pop();
            }
        }
        // for (auto pt : postfixTokens)
        //    cout << pt.first << " ";
        // cout << "\n";
    }
    while (!algoStack.empty() && algoStack.top().first != "(")
    {
        postfixTokens.push_back(algoStack.top());
        algoStack.pop();
    }
    if (!algoStack.empty())
    {
        cout << "Error in brackets!";
        exit(BRACKETS_ERROR);
    }
    // cout << "----------------------\n";
}

double calcPostfixTokensExpression(vector<pair<string, bool>>& postfixTokens)
{
    stack<double> calcStack;
    for (auto pt : postfixTokens)
    {
        // cout << "fuck: " << pt.first << "\n";
        if (!isOperator(pt.first) && !isFunction(pt.first))
        {
            double ans = 1;
            int ip = 0;
            int num = -1;
            while (ip < pt.first.size())
            {
                bool flag = false;
                if (pt.first[ip] == '$')
                {
                    string valueCode = "$";
                    ip++;
                    while (pt.first[ip] != '$')
                    {
                        valueCode += pt.first[ip];
                        ip++;
                    }
                    valueCode += '$';
                    // cout << valueCode << "\n";
                    ans *= NodesCalculatedValuesMap[valueCode];
                    flag = true;
                    ip++;
                }
                else if (pt.first[ip] == 'x')
                {
                    ans *= xVALUE;
                    ip++;
                    flag = true;
                }
                else if (pt.first[ip] == 't')
                {
                    ans *= tVALUE;
                    ip++;
                    flag = true;
                }
                else if (ip + 2 <= pt.first.size() && pt.first.substr(ip, 2) == "pi")
                {
                    ans *= M_PI;
                    ip += 2;
                    flag = true;
                }
                else
                {
                    if (num < 0)
                        num = pt.first[ip] - '0';
                    else
                        num = num * 10 + pt.first[ip] - '0';
                    ip++;
                }
                if (flag && num > -1)
                {
                    ans *= num;
                    num = -1;
                }
            }
            if (num > -1)
            {
                ans *= num;
                num = -1;
            }
            if (pt.second)
                ans *= -1;
            // cout << "ans: " << ans << "\n";
            calcStack.push(ans);
        }
        else if (isOperator(pt.first))
        {
            double first = calcStack.top();
            calcStack.pop();
            double second = calcStack.top();
            calcStack.pop();
            if (pt.first == "+")
                calcStack.push(second + first);
            if (pt.first == "-")
                calcStack.push(second - first);
            if (pt.first == "*")
                calcStack.push(first * second);
            if (pt.first == "/")
            {
                if (abs(first) < 1e-6)
                {
                    cout << "Division on zero. Error!";
                    exit(DIVISION_ZERO_ERROR);
                }
                calcStack.push(second / first);

            }
            if (pt.first == "^")
                calcStack.push(pow(second, first));
        }
        else {
            double value = calcStack.top();
            // cout << "-->" << value << "\n";
            calcStack.pop();
            // cout << "-->?" << value << "\n";
            if (pt.first == "cos")
            {
                if (pt.second)
                    calcStack.push(-cos(value));
                else
                    calcStack.push(cos(value));
            }
            if (pt.first == "sin")
            {
                // cout << value << " " << sin(value) << "\n";
                if (pt.second)
                    calcStack.push(-sin(value));
                else
                    calcStack.push(sin(value));
            }
            if (pt.first == "tg")
            {
                if (pt.second)
                    calcStack.push(-tan(value));
                else
                    calcStack.push(tan(value));
            }
            if (pt.first == "ctg")
            {
                if (pt.second)
                    calcStack.push(-tan(M_PI / 2 - value));
                else
                    calcStack.push(tan(M_PI / 2 - value));
            }
            if (pt.first == "ln")
            {
                if (value <= 0)
                {
                    cout << "Num in ln <= 0. Error!";
                    exit(LOG_ERROR);
                }
                else
                {
                    if (pt.second)
                        calcStack.push(-log(value));
                    else
                        calcStack.push(log(value));
                }
            }
            if (pt.first == "sqrt")
            {
                if (value < 0)
                {
                    cout << "Num in sqrt < 0. Error!";
                    exit(SQRT_ERROR);
                }
                else
                {
                    if (pt.second)
                        calcStack.push(-sqrt(value));
                    else
                        calcStack.push(sqrt(value));
                }
            }
            if (pt.first == "exp")
                calcStack.push(exp(value));
        }
    }
    return calcStack.top();
}

inline double Node::calcValue()
{
    return m_calcValue;
}

void Node::clear()
{
    m_expression = "";
    m_calcValue = 0;
    m_tokens.clear();
    m_postfixTokens.clear();
}

void Node::calcExpression()
{
    for (auto& child : m_childs)
        child->calcExpression();
    for (auto terminal : Terminals)
    {
        if (m_value == terminal)
        {
            m_expression = m_value;
            return;
        }
    }
    for (auto& child : m_childs)
    {
        m_expression += child->expression();
        child->clear();
    }
    if (m_value == "E")
    {
        collectTokens();
        // for (auto t : m_tokens)
            // cout << "{" << t.first << ", " << t.second << "} ";
        // cout << "\n";
        transferToPostfixTokens(m_tokens, m_postfixTokens);
        m_calcValue = calcPostfixTokensExpression(m_postfixTokens);
        m_expression = "$" + to_string(NodesCalculatedValuesMap.size()) + "$";
        NodesCalculatedValuesMap[m_expression] = m_calcValue;
    }
}

void Node::collectTokens()
{
    int ip = 0;
    bool haveMinus = false;
    bool minusFlag = false;
    vector<pair<string, bool>> tmp;
    while (ip < m_expression.size())
    {
        // cout << ip << " " << m_expression.size() << " " << m_expression << "\n";
        string calcValueCode = "$";
        if (m_expression[ip] == '$')
        {
            ip++;
            while (m_expression[ip] != '$')
            {
                calcValueCode += m_expression[ip];
                ip++;
            }
            calcValueCode += '$';
            ip++;
        }
        if (calcValueCode.size() > 1 && minusFlag) // here
        {
            if (tmp.empty() || (tmp.back().first == "-" || tmp.back().first == "+"
                || tmp.back().first == "*" || tmp.back().first == "/" ||
                tmp.back().first == "(" || tmp.back().first == "^"))
                tmp.push_back({ calcValueCode, haveMinus });
            else
            {
                if (haveMinus)
                    tmp.push_back({ "-", false });
                else
                    tmp.push_back({ "+", false });
                tmp.push_back({ calcValueCode, false });
            }
            haveMinus = false;
            minusFlag = false;
        }
        else if (calcValueCode.size() > 1)
            tmp.push_back({ calcValueCode, false });
        for (auto word : UsedWords)
        {
            bool flag = false;
            if (ip + word.size() <= m_expression.size() && m_expression.substr(ip, word.size()) == word)
            {
                if (word == "-")
                {
                    haveMinus ^= true;
                    minusFlag = true;
                }
                else if (minusFlag)
                {
                    if (tmp.empty() || (tmp.back().first == "-" || tmp.back().first == "+"
                        || tmp.back().first == "*" || tmp.back().first == "/" ||
                        tmp.back().first == "(" || tmp.back().first == "^"))
                        tmp.push_back({ word, haveMinus });
                    else
                    {
                        if (haveMinus)
                            tmp.push_back({ "-", false });
                        else
                            tmp.push_back({ "+", false });
                        tmp.push_back({ word, false });
                    }
                    haveMinus = false;
                    minusFlag = false;
                }
                else
                    tmp.push_back({ word, false });
                ip += word.size();
                break;
            }
        }
    }
    for (auto p : tmp)
    {
        // cout << p.first << "\n";
        if (isDigit(p.first))
        {
            if (!m_tokens.empty() && m_tokens.back().first.back() >= '0'
                && m_tokens.back().first.back() <= '9')
            {
                m_tokens.back().first += p.first;
                m_tokens.back().second ^= p.second;
            }
            else if (!m_tokens.empty() && (!isOperator(m_tokens.back().first)
                || m_tokens.back().first == ")"))
            {
                m_tokens.push_back({ "*", false });
                m_tokens.push_back(p);
            }
            else
                m_tokens.push_back(p);
        }
        else if (isMathVariable(p.first) || isFunction(p.first) || isConstant(p.first))
        {
            if (!m_tokens.empty() && (!isOperator(m_tokens.back().first)
                || m_tokens.back().first == ")"))
                m_tokens.push_back({ "*", false });
            m_tokens.push_back(p);
        }
        else if (p.first == "(")
        {
            if (!m_tokens.empty() && (!isOperator(m_tokens.back().first)
                && !isFunction(m_tokens.back().first) || m_tokens.back().first == ")"))
                m_tokens.push_back({ "*", false });
            m_tokens.push_back(p);
        }
        else
            m_tokens.push_back(p);
    }
}

/* void Node::collectExpression()
{
    for (auto terminal : Terminals)
    {
        if (m_value == terminal)
        {
            m_expression = m_value;
            return;
        }
    }
    for (auto& child : m_childs)
    {
        child->collectExpression();
        m_expression += child->expression();
    }
};*/

inline string Node::expression()
{
    return m_expression;
}

void Node::printTree(int level)
{
    for (int i = 0; i < level; i++)
        cout << "  ";
    cout << m_value << " " << m_expression << " ";
    if (m_value == "E")
    {
        cout << "ok" << " ";
        for (auto t : m_tokens)
            cout << "{" << t.first << " " << t.second << "} ";
        cout << "| ";
        for (auto pt : m_postfixTokens)
            cout << "{" << pt.first << " " << pt.second << "} ";
    }
    cout << "\n";
    for (auto& child : m_childs)
        child->printTree(level + 1);
}

void Node::reverseTree()
{
    reverse(m_childs.begin(), m_childs.end());
    for (auto& child : m_childs)
        child->reverseTree();
}

inline int Node::childsSize()
{
    return m_childs.size();
}

Node::Node(Node* parent, string& value) :
    m_value(value),
    m_parent(parent)
{};

inline Node* Node::backChild()
{
    return m_childs.back().get();
}

inline void Node::setParent(Node* parent)
{
    m_parent = parent;
}

inline void Node::setValue(string& value)
{
    m_value = value;
}

inline void Node::addChild(string& value)
{
    m_childs.push_back(make_unique<Node>(this, value));
}

inline string Node::value() const
{
    return m_value;
}

inline Node* Node::parent() const
{
    return m_parent;
}

inline Node* Node::child(int inx) const
{
    return m_childs[inx].get();
}

set<string> fromTokensFIRST(vector<string>& tokens)
{
    set<string> first;
    bool haveEpsilon = true;
    for (int i = 0; i < tokens.size() && haveEpsilon; i++)
    {
        haveEpsilon = false;
        for (auto s : FIRST[tokens[i]])
        {
            haveEpsilon = haveEpsilon || s.empty();
            if (!s.empty())
                first.insert(s);
        }
    }
    if (haveEpsilon)
        first.insert("");
    return first;
}

void printFIRST()
{
    for (auto p : FIRST)
    {
        cout << p.first << ": {";
        if (p.second.size() > 0)
        {
            for (set<string> ::iterator it = p.second.begin(); it != --p.second.end(); it++)
            {
                if ((*it).empty())
                    cout << "eps";
                else
                    cout << *it;
                cout << ", ";
            }
            if ((*(--p.second.end())).empty())
                cout << "eps";
            else
                cout << *(--p.second.end());
        }
        cout << "}\n";
    }
}

void printFOLLOW()
{
    for (auto p : FOLLOW)
    {
        cout << p.first << ": {";
        if (p.second.size() > 0)
        {
            for (set<string> ::iterator it = p.second.begin(); it != --p.second.end(); it++)
            {
                if ((*it).empty())
                    cout << "eps";
                else
                    cout << *it;
                cout << ", ";
            }
            if ((*(--p.second.end())).empty())
                cout << "eps";
            else
                cout << *(--p.second.end());
        }
        cout << "}\n";
    }
}

set<string> intersectionOfSets(set<string> a, set<string> b)
{
    set<string>intersectionSet;
    while (!a.empty() && !b.empty())
    {
        if (*a.begin() < *b.begin())
            a.erase(a.begin());
        else if (*a.begin() > *b.begin())
            b.erase(b.begin());
        else
        {
            intersectionSet.insert(*a.begin());
            a.erase(a.begin());
            b.erase(b.begin());
        }
    }
    return intersectionSet;
}

map<string, vector<vector<string>>> tokensFromGrammar(map<string, vector<string>>& grammar,
    vector<string>& terminals, vector<string>& notTerminals)
{
    map<string, vector<vector<string>>>tokensGrammar;
    for (auto notTerminal : notTerminals)
    {
        for (auto prod : grammar[notTerminal])
        {
            vector<string>tokens;
            int inx = 0;
            if (prod.empty())
                tokens.push_back("");
            else
            {
                while (inx < prod.size())
                {
                    string choosenTerminal = "";
                    string choosenNotTerminal = "";
                    for (auto terminal : terminals)
                    {
                        if (inx + terminal.size() <= prod.size()
                            && prod.substr(inx, terminal.size()) == terminal
                            && terminal.size() > choosenTerminal.size())
                            choosenTerminal = terminal;
                    }
                    if (!choosenTerminal.empty())
                    {
                        tokens.push_back(choosenTerminal);
                        inx += choosenTerminal.size();
                    }
                    for (auto notTerminal : notTerminals)
                    {
                        if (inx + notTerminal.size() <= prod.size()
                            && prod.substr(inx, notTerminal.size()) == notTerminal)
                            choosenNotTerminal = notTerminal;
                    }
                    if (!choosenNotTerminal.empty())
                    {
                        tokens.push_back(choosenNotTerminal);
                        inx += choosenNotTerminal.size();
                    }
                }
            }
            tokensGrammar[notTerminal].push_back(tokens);
        }
    }
    return tokensGrammar;
}

void fillTable(map<string, vector<string>>& grammar,
    vector<string>& terminals, vector<string>& notTerminals)
{
    map<string, vector<pair<string, vector<string>>>> terminalsMap;
    for (auto terminal : terminals)
        terminalsMap[terminal] = vector<pair<string, vector<string>>>();
    terminalsMap["$"] = vector<pair<string, vector<string>>>();
    for (auto notTerminal : notTerminals)
        SyntaxAnalyseTable[notTerminal] = terminalsMap;
    map<string, vector<vector<string>>>tokensGrammar =
        tokensFromGrammar(grammar, terminals, notTerminals);
    for (auto p : tokensGrammar)
    {
        for (auto tokens : p.second)
        {
            set<string> first = fromTokensFIRST(tokens);
            for (auto a : first)
            {
                if (a.empty())
                {
                    for (auto b : FOLLOW[p.first])
                    {
                        for (auto q : terminals)
                        {
                            if (b == q)
                            {
                                SyntaxAnalyseTable[p.first][b].push_back({ p.first, tokens });
                                break;
                            }
                        }
                        if (b == "$")
                            SyntaxAnalyseTable[p.first][b].push_back({ p.first, tokens });
                    }
                }
                for (auto q : terminals)
                {
                    if (q == a)
                    {
                        SyntaxAnalyseTable[p.first][a].push_back({ p.first, tokens });
                        break;
                    }
                }
            }
        }
    }
}

void printTable()
{
    for (auto p : SyntaxAnalyseTable)
    {
        for (auto v : p.second)
        {
            cout << "(" << p.first << ", " << v.first << "): ";
            for (auto q : v.second)
            {
                cout << q.first << "-->";
                for (auto c : q.second)
                    cout << c << " ";
                cout << "|";
            }
            cout << "size: " << v.second.size() << "\n";
        }
    }
}

bool checkLL(map<string, vector<string>>& grammar, vector<string>& terminals,
    vector<string>& notTerminals)
{
    map<string, vector<vector<string>>>tokensGrammar =
        tokensFromGrammar(grammar, terminals, notTerminals);
    bool isLL = true;
    for (auto p : tokensGrammar)
    {
        for (int i = 0; i < p.second.size(); i++)
        {
            set<string>alphaFirst = fromTokensFIRST(p.second[i]);
            for (int j = i + 1; j < p.second.size(); j++)
            {
                set<string>bettaFirst = fromTokensFIRST(p.second[j]);
                set<string>intersectionResult = intersectionOfSets(alphaFirst, bettaFirst);
                isLL = isLL && intersectionResult.empty();
                if (alphaFirst.find("") != alphaFirst.end())
                {
                    intersectionResult = intersectionOfSets(bettaFirst, FOLLOW[p.first]);
                    isLL = isLL && intersectionResult.empty();
                }
            }
        }
    }
    return isLL;
}

void fillFOLLOW(map<string, vector<string>>& grammar, vector<string>& terminals,
    vector<string>& notTerminals, string& startNotTerminal)
{
    FOLLOW[startNotTerminal].insert("$");
    map<string, vector<vector<string>>>tokensGrammar =
        tokensFromGrammar(grammar, terminals, notTerminals);
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (auto notTerminal : notTerminals)
        {
            for (auto tokens : tokensGrammar[notTerminal])
            {
                vector<string>afterTokens = tokens;
                reverse(afterTokens.begin(), afterTokens.end());
                for (int i = 0; i < tokens.size(); i++)
                {
                    afterTokens.pop_back();
                    if (tokensGrammar.find(tokens[i]) != tokensGrammar.end())
                    {
                        reverse(afterTokens.begin(), afterTokens.end());
                        set<string> gettedFirst = fromTokensFIRST(afterTokens);
                        reverse(afterTokens.begin(), afterTokens.end());
                        int startCount = FOLLOW[tokens[i]].size();
                        for (auto s : gettedFirst)
                        {
                            if (!s.empty())
                                FOLLOW[tokens[i]].insert(s);
                        }
                        if (gettedFirst.find("") != gettedFirst.end())
                        {
                            for (auto s : FOLLOW[notTerminal])
                                FOLLOW[tokens[i]].insert(s);
                        }
                        flag = flag || startCount < FOLLOW[tokens[i]].size();
                    }
                }
            }
        }
    }
}

void fillFIRST(map<string, vector<string>>& grammar,
    vector<string>& terminals, vector<string>& notTerminals)
{
    for (auto s : terminals)
        FIRST[s].insert(s);
    FIRST[""].insert("");
    map<string, vector<vector<string>>>tokensGrammar =
        tokensFromGrammar(grammar, terminals, notTerminals);
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (auto notTerminal : notTerminals)
        {
            int startCount = FIRST[notTerminal].size();
            for (auto tokens : tokensGrammar[notTerminal])
            {
                bool haveEpsilon;
                for (int i = 0; i < tokens.size(); i++)
                {
                    haveEpsilon = true;
                    for (int j = 0; j < i && haveEpsilon; j++)
                        haveEpsilon = FIRST[tokens[j]].find("") != FIRST[tokens[j]].end();
                    if (haveEpsilon)
                    {
                        for (auto a : FIRST[tokens[i]])
                            FIRST[notTerminal].insert(a);
                    }
                }
                haveEpsilon = true;
                for (int i = 0; i < tokens.size() && haveEpsilon; i++)
                    haveEpsilon = FIRST[tokens[i]].find("") != FIRST[tokens[i]].end();
                if (haveEpsilon)
                    FIRST[notTerminal].insert("");
            }
            flag = flag || startCount < FIRST[notTerminal].size();
        }
    }
}

void initGrammar()
{
    Grammar["F"] = { "C", "N", "(E)", "-F", "sqrt(E)",
        "sin(E)", "cos(E)", "tg(E)", "ctg(E)", "-F", "ln(E)", "exp(E)" };
    Grammar["T"] = { "F", "TF", "T/F" };
    Grammar["E"] = { "T", "E+T", "E-T", "E^T" };
    Grammar["C"] = { "NC", "x", "t" };
    Grammar["N"] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    for (char i = '0'; i <= '9'; i++)
    {
        string s = "N";
        s += i;
        Grammar["N"].push_back(s);
    }
}

void printGrammar(map<string, vector<string>>& grammar)
{
    for (auto elem : grammar)
    {
        cout << elem.first << "-->";
        for (int i = 0; i < elem.second.size() - 1; i++)
            cout << elem.second[i] << "|";
        cout << elem.second.back() << "\n";
    }
}

void initVariables()
{
    for (char i = 'A'; i <= 'Z'; i++)
    {
        if (i == 'O') continue;
        string s = "";
        s += i;
        Variables.push_back(s);
    }
    for (char i = 'A'; i <= 'Z'; i++)
    {
        if (i == 'O') continue;
        string s = "1";
        s = i + s;
        Variables.push_back(s);
    }
}

void deleteDirectRecursion(string recursionVariable, map<string, vector<string>>& grammar)
{
    vector<string>afterVar(0);
    vector<string>beforeVar(0);
    for (auto elem : grammar[recursionVariable])
    {
        if (elem.empty())
        {
            beforeVar.push_back(elem);
            continue;
        }
        bool flag = true;
        for (int inx = 0; inx < min(elem.size(), recursionVariable.size()) && flag; inx++)
            flag = elem[inx] == recursionVariable[inx];
        if (!flag) beforeVar.push_back(elem);
        else afterVar.push_back(elem.substr(min(elem.size(), recursionVariable.size())));
    }
    if (afterVar.empty())
        return;
    for (auto var : Variables)
    {
        if (grammar.find(var) == grammar.end())
        {
            for (int i = 0; i < beforeVar.size(); i++)
                beforeVar[i] += var;
            for (int i = 0; i < afterVar.size(); i++)
                afterVar[i] = afterVar[i] + var;
            afterVar.push_back("");
            if (beforeVar.empty())
                beforeVar.push_back(var);
            grammar[recursionVariable] = beforeVar;
            grammar[var] = afterVar;
            return;
        }
    }
}

void clearLeftRecursion(map<string, vector<string>>& grammar)
{
    vector<string> variables(0);
    for (auto p : grammar) variables.push_back(p.first);
    for (int i = 0; i < variables.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            int count = 0;
            vector<string>newGrammarVector(0);
            for (int k = 0; k < grammar[variables[i]].size(); k++)
            {
                string elem = grammar[variables[i]][k];
                if (elem.empty())
                {
                    newGrammarVector.push_back(grammar[variables[i]][k]);
                    continue;
                }
                bool flag = true;
                for (int inx = 0; inx < min(elem.size(), variables[j].size()) && flag; inx++)
                    flag = elem[inx] == variables[j][inx];
                if (flag)
                {
                    string rightPart = elem.substr(min(elem.size(), variables[j].size()));
                    for (auto q : grammar[variables[j]])
                    {
                        string s = q + rightPart;
                        newGrammarVector.push_back(s);
                    }
                }
                else
                    newGrammarVector.push_back(grammar[variables[i]][k]);
            }
            grammar[variables[i]] = newGrammarVector;
        }
        deleteDirectRecursion(variables[i], grammar);
    }
}

void replaceProduction(string& variable, map<string, vector<string>>& grammar, string& prefix)
{
    string newVar;
    for (auto var : Variables)
    {
        if (grammar.find(var) == grammar.end())
        {
            newVar = var;
            break;
        }
    }
    vector<string>newGrammarVector(0);
    vector<string>newVarGrammarVector(0);
    for (int i = 0; i < grammar[variable].size(); i++)
    {
        bool flag = grammar[variable][i].size() >= prefix.size();
        for (int j = 0; j < prefix.size() && flag; j++)
            flag = prefix[j] == grammar[variable][i][j];
        if (flag)
            newVarGrammarVector.push_back(grammar[variable][i].substr(prefix.size()));
        else
            newGrammarVector.push_back(grammar[variable][i]);
    }
    for (auto p : grammar)
    {
        if (p.second == newVarGrammarVector)
        {
            newGrammarVector.push_back(prefix + p.first);
            grammar[variable] = newGrammarVector;
            return;
        }
    }
    newGrammarVector.push_back(prefix + newVar);
    grammar[newVar] = newVarGrammarVector;
    grammar[variable] = newGrammarVector;
}

void leftFactorisation(map<string, vector<string>>& grammar)
{
    for (map<string, vector<string>> ::iterator it = grammar.begin(); it != grammar.end(); it++)
    {
        int count = (int)1e9;
        while (count > 1)
        {
            count = 1;
            string prefix = "";
            map<string, int>prefixCountMap;
            for (int i = 0; i < it->second.size(); i++)
            {
                string s = "";
                for (int j = 0; j < it->second[i].size(); j++)
                {
                    s += it->second[i][j];
                    prefixCountMap[s]++;
                }
            }
            for (auto p : prefixCountMap)
            {
                if (p.second > 1 && p.first.size() > prefix.size())
                {
                    count = p.second;
                    prefix = p.first;
                }
            }
            if (count > 1)
            {
                string currentVariable = it->first;
                replaceProduction(currentVariable, grammar, prefix);
            }
        }
    }
}

void getLLFromMyGrammar()
{
    clearLeftRecursion(Grammar);
    leftFactorisation(Grammar);
    Grammar["G"].pop_back();
    Grammar["L"].erase(Grammar["L"].begin());
    Grammar["D"].push_back("*FD");
    Grammar["C"].push_back("pi");
    Grammar["F"].push_back("pi");
    Grammar["T"].push_back("piD");
    // clearLeftRecursion(Grammar);
    // leftFactorisation(Grammar);
    fillFIRST(Grammar, Terminals, NotTerminals);
    fillFOLLOW(Grammar, Terminals, NotTerminals, StartNotTerminal);
    printFOLLOW();
    if (checkLL(Grammar, Terminals, NotTerminals))
        cout << "Success!\n";
    else
        cout << "Fail!\n";
}

bool analyseExpression(string expression, string& startNotTerminal,
    vector<string>& terminals, vector<string>& notTerminals, unique_ptr<Node>& parseTree)
{
    expression += "$";
    stack<Node*> expressionStack;
    string endSymbol = "$";
    unique_ptr<Node> endNode = make_unique<Node>(nullptr, endSymbol);
    expressionStack.push(endNode.get());
    expressionStack.push(parseTree.get());
    int ip = 0;
    string currentString = "";
    while (expressionStack.top()->value() != "$")
    {
        Node* parentNode = expressionStack.top();
        string X = expressionStack.top()->value();
        if (currentString.empty())
        {
            for (auto terminal : terminals)
            {
                if (expression.substr(ip, terminal.size()) == terminal)
                {
                    currentString = terminal;
                    break;
                }
            }
            if (expression.substr(ip) == "$")
                currentString = "$";
        }
        if (X == currentString)
        {
            // cout << "equality: " << X << "\n";
            expressionStack.pop();
            ip += currentString.size();
            currentString = "";
        }
        else {
            bool flag = false;
            for (auto notTerminal : notTerminals)
            {
                if (X == notTerminal)
                {
                    if (SyntaxAnalyseTable[X][currentString].empty())
                        return false;
                    else
                    {
                        flag = true;
                        pair<string, vector<string>> p = SyntaxAnalyseTable[X][currentString][0];
                        // cout << p.first << "-->";
                        // for (auto c : p.second)
                        //   cout << c;
                        // cout << "\n";
                        expressionStack.pop();
                        vector<string>tmp = p.second;
                        reverse(tmp.begin(), tmp.end());
                        for (auto c : tmp)
                        {
                            if (!c.empty())
                            {
                                parentNode->addChild(c);
                                expressionStack.push(parentNode->backChild());
                            }
                        }
                        break;
                    }
                }
            }
            if (!flag)
                return false;
        }
    }
    return true && expression[ip] == '$';
}

bool comp(string& a, string& b)
{
    return a.size() < b.size();
}

class Tester
{
public:
    Tester();
    void testing();
    void addTest(string expression, double(*executeExpression)(double, double), 
        vector<pair<double, double>> mathVariablesValues = {});
    void addMathVariablesValuesForTest(
        string testExpression, double x, double t);
private:
    map<string, double(*)(double, double)> m_tests;
    // first -> x
    // second -> t
    map<string, vector<pair<double, double>>> m_mathVariablesValues;
};

// sin(x^3)cos(t^(x/15))2/tx+2t^3
double executeExpression1(double x, double t)
{
    return sin(pow(x, 3)) * cos(pow(t, (x / 15))) * 2 / t * x + 2 * pow(t, 3);
}

// 2xt
double executeExpression2(double x, double t)
{
    return 2 * x * t;
}

// t^(x/15)
double executeExpression3(double x, double t)
{
    return pow(t, (x / 15));
}

// 15/(7-(1+1))3-(2+(1+1))15/(7-(200+1))3-(2+(1+1))(15/(7-(1+1))3-(2+(1+1))+15/(7-(1+1))3-(2+(1+1)))
// ответ посчитан на питоне -30.072164948453608
double executeExpression4(double x, double t)
{
    return -30.072164948453608;
}

// x+t^(sin(5xt)cos(x^x^6))
double executeExpression5(double x, double t)
{
    return x + pow(t, sin(5*x*t) * cos(pow(pow(x, x), 6)));
}

// 1-txpi*cos(pit)
double executeExpression6(double x, double t)
{
    return 1 - t * x * M_PI * cos(M_PI * t);
}

// 1+---sqrt(2)x
double executeExpression7(double x, double t)
{
    return 1 + -(-(-sqrt(2))) * x;
}

// -(-x--t+--(-2-5x))
double executeExpression8(double x, double t)
{
    return -(-x - (-t) + -(-(-2 - 5 * x)));
}

// (1+t)+-(-x+-4t)
double executeExpression9(double x, double t)
{
    return (1 + t) + -(-x + -4 * t);
}

// pi/3xt^1/2x
double executeExpression10(double x, double t)
{
    return M_PI / 3 * x * t / 2 * x;
}

// ---ln(x)+-cos(x)--sin(x)
double executeExpression11(double x, double t)
{
    return -(-(-log(x))) + -cos(x) - (-sin(x));
}

// (((x)pi/(3xt)^1/2x))
double executeExpression12(double x, double t)
{
    return ((x) * M_PI / (3 * x * t) / 2 * x);
}

// -(---x--3*---2t)
double executeExpression13(double x, double t)
{
    return -(-(-(-x)) - -3*-(-(-2*t)));
}

// -cos(-2x)sin(-2x)-(---4-7)xtx
double executeExpression14(double x, double t)
{
    return -cos(-2 * x) * sin(-2 * x) - (-(-(-4)) - 7) * x * t * x;
}

// -2tln(exp(1))-(-cos(25xt)888+-sin(1111)+13exp(6))
double executeExpression15(double x, double t)
{
    return -2 * t * log(exp(1)) - (-cos(25 * x * t) * 888 + -sin(1111) + 13 * exp(6));
}

// ln(18)/ln(2)/pi*sqrt((11/100)^(-3)*100/2)
double executeExpression16(double x, double t)
{
    return log(18)/log(2)/M_PI*sqrt(pow((11.0 / 100.0), -3) * 100 / 2);
}

// (-x27)(--x/5)(---t)
double executeExpression17(double x, double t)
{
    return (-x*27)*(-(-x)/5)*-(-(-t));
}

// 200t^3
double executeExpression18(double x, double t)
{
    return 200*pow(t, 3);
}

// 200t^-3
double executeExpression19(double x, double t)
{
    return 200 * pow(t, -3);
}

// 1/-9
double executeExpression20(double x, double t)
{
    return 1.0/-9.0;
}

// 2xt^--(--x^-3+5/-9t)
double executeExpression21(double x, double t)
{
    return 2 * x * pow(t, -(-(-(-pow(x, -3)) + 5.0 / -9.0 * t)));
    // 2*x*pow(t, -(-(-(-pow(x, -3))+5/-9*t)));
}

Tester::Tester()
{
    addTest("2xt", executeExpression2, {{1, 0}, {-2, 7}, {33, -11}});
    addTest("sin(x^3)cos(t^(x/15))2/tx+2t^3", executeExpression1,
        { {M_PI / 2, M_PI / 8}, {-20 * M_PI / 2, M_PI + 10 / 8}, {35, 26}, { 7, 23 } });
    addTest("t^(x/15)", executeExpression3, { {7, 23} });
    addTest("15/(7-(1+1))3-(2+(1+1))15/(7-(200+1))3-(2+(1+1))(15/(7-(1+1))3-(2+(1+1))+15/(7-(1+1))3-(2+(1+1)))",
        executeExpression4, { {1, 1}, {-2, -3} });
    addTest("x+t^(sin(5xt)cos(x^x^6))",
        executeExpression5, { {(M_PI + 236) / 321.0, M_PI * M_PI * M_PI / 25.0}, 
        {25, 0}, {11, 3 * M_PI} });
    addTest("1-txpi*cos(pit)",
        executeExpression6, { {(M_PI + 236) / 321.0, M_PI * M_PI * M_PI / 25.0},
        {17, -10}, {-11, -3 * M_PI} });
    addTest("1+---sqrt(2)x", executeExpression7, { {-62.354, 727.734},
        {-733.311, -966.223}, {-126.504, 213.409} });
    addTest("-(-x--t+--(-2-5x))", executeExpression8, { {530.9, -87.564},
        {-171.098, 560.32}, {32.736, -351.14} });
    addTest("(1+t)+-(-x+-4t)", executeExpression9, { {828.457, 488.669},
        {56.466, -983.201}, {-350.11, 271.453} });
    addTest("pi/3xt^1/2x", executeExpression10, { {386.617, 156.115},
        {319.497, 387.655}, {-897.75, 871.51} });
    addTest("---ln(x)+-cos(x)--sin(x)", executeExpression11, { {771.174, 670.509},
        {225.049, -818.449}, {368.900, -797.374} });
    addTest("(((x)pi/(3xt)^1/2x))", executeExpression12, { {771.174, 670.509},
        {225.049, -818.449}, {368.900, -797.374} });
    addTest("-(---x--3*---2t)", executeExpression13, { {771.174, 670.509},
        {225.049, -818.449}, {368.900, -797.374} });
    addTest("-cos(-2x)sin(-2x)-(---4-7)xtx", executeExpression14, { {771.174, 670.509},
        {225.049, -818.449}, {368.900, -797.374} });
    addTest("-2tln(exp(1))-(-cos(25xt)888+-sin(1111)+13exp(6))", executeExpression15, { {771.174, 670.509},
        {225.049, -818.449}, {368.900, -797.374} });
    addTest("ln(18)/ln(2)/pi*sqrt((11/100)^(-3)*100/2)", executeExpression16, { {0, 0} });
    addTest("(-x27)(--x/5)(---t)", executeExpression17, { {771.174, 670.509},
        {225.049, -818.449}, {368.900, -797.374} });
    addTest("200t^3", executeExpression18, { {2.392, 7.013},
        {1.725, 9.846}, {12.003, -11.334} });
    addTest("200t^-3", executeExpression19, { {2.392, 7.013},
        {1.725, 9.846}, {12.003, -11.334} });
    addTest("1/-9", executeExpression20, { {2.392, 7.013},
        {1.725, 9.846}, {12.003, -11.334} });
    addTest("2xt^--(--x^-3+5/-9t)", executeExpression21, { {2.392, 7.013},
        {1.725, 9.846}, {12, 11} }); // 2xt^--(--x^-3+5/-9t)
};

inline void Tester::addTest(string expression, double(*executeExpression)(double, double), 
    vector<pair<double, double>> mathVariablesValues)
{
    m_tests[expression] = executeExpression;
    m_mathVariablesValues[expression] = {};
    for (auto values : mathVariablesValues)
        addMathVariablesValuesForTest(expression, values.first, values.second);
}

inline void Tester::addMathVariablesValuesForTest(
    string testExpression, double x, double t)
{
    if (m_mathVariablesValues.find(testExpression)
        != m_mathVariablesValues.end())
        m_mathVariablesValues[testExpression].push_back({ x, t });
}

void Tester::testing()
{
    int testNumber = 0;
    unique_ptr<Node> parseTree = make_unique<Node>(nullptr, StartNotTerminal);
    for (auto test : m_tests)
    {
        int acceptedTestsCount = 0;
        int failedTestsCount = 0;
        unique_ptr<Node> parseTree = make_unique<Node>(nullptr, StartNotTerminal);
        bool resultOfAnalyseExpression = analyseExpression(test.first, StartNotTerminal,
            Terminals, NotTerminals, parseTree);
        parseTree->reverseTree();
        vector<pair<double, double>> testResults;
        if (resultOfAnalyseExpression)
        {
            for (auto data : m_mathVariablesValues[test.first])
            {
                NodesCalculatedValuesMap.clear();
                // cout << "size: " << NodesCalculatedValuesMap.size() << "\n";
                xVALUE = data.first;
                tVALUE = data.second;
                double compilerAnswer = test.second(data.first, data.second);
                parseTree->calcExpression();
                // parseTree->printTree(0);
                double myCalculatorAnswer = parseTree->calcValue();
                parseTree->clear();
                testResults.push_back({ compilerAnswer, myCalculatorAnswer });
            }
            int dataNumber = 0;
            int acceptedTestsCount = 0;
            bool flag = true;
            for (auto data : m_mathVariablesValues[test.first])
            {
                if (abs(testResults[dataNumber].first - testResults[dataNumber].second) < 1e-6)
                    acceptedTestsCount++;
                else
                {
                    if (flag)
                    {
                        cout << "----------------------------------------------------------\n";
                        cout << "Test" << testNumber << ":\n";
                        cout << "expression: " << test.first << "\n";
                        flag = false;
                    }
                    cout << "\nx=" << data.first << " t=" << data.second << "\n";
                    cout << "compilerAnswer: " << testResults[dataNumber].first << "\n";
                    cout << "myCalculatorAnswer: " << testResults[dataNumber].second << "\n";
                    cout << "Verdict: Failed\n";
                }
                dataNumber++;
            }
            if (acceptedTestsCount < m_mathVariablesValues[test.first].size())
            {
                cout << "\nResult of testing: " << acceptedTestsCount
                    << "/" << m_mathVariablesValues[test.first].size() << "\n";
                cout << "CommonVerdict: ";
                if (acceptedTestsCount == m_mathVariablesValues[test.first].size())
                    cout << "Accepted";
                else
                    cout << "Failed";
                cout << "\n";
                cout << "----------------------------------------------------------\n";
            }
        }
        else
        {
            cout << "----------------------------------------------------------\n";
            cout << "Test" << testNumber << ":\n";
            cout << "expression: " << test.first << "\n";
            cout << "Данное выражение невозможно посчитать, \n"
                "так как в нем нарушены правила записи математических выраженией\n";
            cout << "----------------------------------------------------------\n";
        }
        testNumber++;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    unique_ptr<Node> parseTree = make_unique<Node>(nullptr, StartNotTerminal);
    initGrammar();
    initVariables();
    sort(Terminals.begin(), Terminals.end(), comp);
    sort(UsedWords.begin(), UsedWords.end(), comp);
    reverse(Terminals.begin(), Terminals.end());
    reverse(UsedWords.begin(), UsedWords.end());
    map<string, vector<string>> tmpGrammar;
    getLLFromMyGrammar();
    fillTable(Grammar, Terminals, NotTerminals);
    Tester tester;
    tester.testing();
    printGrammar(Grammar);
    bool resultOfAnalyseExpression = analyseExpression(
        "x^2", StartNotTerminal, Terminals,
        NotTerminals, parseTree);
    if (resultOfAnalyseExpression)
    {
        parseTree->reverseTree();
        parseTree->printTree(0);
        xVALUE = 5;
        parseTree->calcExpression();
        cout << parseTree->calcValue();
    }
    else
        cout << "error in expression";
    return 0;
}
