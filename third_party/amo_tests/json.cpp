#include <iostream>

#include <amo/json.hpp>
#include <gtest/gtest.h>




TEST(json, init) {
    nlohmann::json j2({
        { "pi", 3.141 },
        { "happy", true }
        
    });
    
    amo::json json({ { "happy", true } });
    amo::json json3({
        { "pi", 3.141 },
        { "happy", true }
        
    });
}