#include <gtest/gtest.h>
#include "key.hpp"
#include <vector>
#include <string>
#include <fstream>
std::vector<std::vector<Pair>> pairs;
void parse();
bool test(Pair pair, Status* status);

bool run_process(Status* status)
{
    parse();
    bool out = true;
    for (int i = 0; i < pairs.size(); ++i)
    {
        for (int j = 0; j < pairs[i].size(); ++j)
        {
            out = test(pairs[i][j], status);
            if (out == false)
            {
                return false;
            }
        }
        Status tmp;
        status = &tmp;
    }
    return true;
}

bool test(Pair pair, Status* status)
{
    if (status->process((Input)pair.input) == (Output)pair.output)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void parse()
{
    std::string line;
    std::ifstream in("tests.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            char* token;
            token = strtok(&line[0], " /");
            Pair pair = { -1,-1 };
            std::vector<Pair> inPair;
            while (token != nullptr)
            {
                if (pair.input < 0) pair.input = std::stoi(token);
                else pair.output = std::stoi(token);
                if (pair.input >= 0 && pair.output >= 0)
                {
                    inPair.push_back(pair);
                    pair = { -1, -1 };
                }
                token = strtok(nullptr, " /");
            }
            pairs.push_back(inPair);
            inPair.clear();
            int x = 0;

        }
    }
    in.close();
}
TEST(Basic, one)
{
    
    Status status;
    bool res = run_process(&status);
    EXPECT_TRUE(res);
}


int main(int argc, char** argv) 
{
    parse();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
