//
// flat_array_test.cc
// Copyright 2017 4paradigm.com 


#include "base/flat_array.h"
#include "gtest/gtest.h"
#include "base/strings.h"
#include <iostream>

namespace rtidb {
namespace base {

class FlatArrayTest : public ::testing::Test {

public:
    FlatArrayTest() {}
    ~FlatArrayTest() {}
};

TEST_F(FlatArrayTest, Encode) {
    std::string buffer;
    FlatArrayCodec codec(&buffer, 2);
    bool ok = codec.Append(1.2f);
    ASSERT_TRUE(ok);
    ok = codec.Append("helloworld");
    ASSERT_TRUE(ok);
    codec.Build();
    ASSERT_TRUE(buffer.size() == 19);
    std::cout << ::rtidb::base::DebugString(buffer) << std::endl;
    FlatArrayIterator it(buffer.c_str(), buffer.size());
    ASSERT_EQ(kFloat, it.GetType());
    ASSERT_TRUE(it.Valid());
    ASSERT_EQ(2, it.Size());
    float value = 0;
    ok = it.GetFloat(&value);
    ASSERT_TRUE(ok);
    ASSERT_EQ(1.2f, value);
    std::cout << value << std::endl;
    std::string value2;
    it.Next();
    ASSERT_TRUE(it.Valid());
    ok = it.GetString(&value2);
    ASSERT_TRUE(ok);
    ASSERT_EQ("helloworld", value2);
    it.Next();
    ASSERT_FALSE(it.Valid());
    std::string buffer2;
    FlatArrayCodec codec2(&buffer2, 2);
    codec2.Append("wtz");
    codec2.Append(1.0f);
    codec2.Build();
    std::cout << ::rtidb::base::DebugString(buffer2) << std::endl;
}

}
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
