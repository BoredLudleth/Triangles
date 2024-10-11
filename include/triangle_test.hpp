#pragma once
#include <gtest/gtest.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include <vector>
#include "triangle.hpp"

TEST(TestPointConstr1, TrgTest) {
    point<float> p1(1, 2, 3);

    EXPECT_EQ(p1.get_x(), 1);
    EXPECT_EQ(p1.get_y(), 2);
    EXPECT_EQ(p1.get_z(), 3);
    EXPECT_EQ(p1.valid(), 1);
}

TEST(TestPointConstr2, TrgTest) {
    point<float> p1(1, 2, 3);
    point<float> p2 = p1;

    EXPECT_EQ(p2.get_x(), 1);
    EXPECT_EQ(p2.get_y(), 2);
    EXPECT_EQ(p2.get_z(), 3);
    EXPECT_EQ(p2.valid(), 1);
}

TEST(TestPointLength, TrgTest) {
    point<float> p1(1, 2, 3);

    EXPECT_EQ(p1.length(), 14);
}

TEST(TestPointOperations, TrgTest) {
    point<float> p1(1,  2, 3);
    point<float> p2(-1, 0, 1);

    EXPECT_EQ(p1 + p2, point<float>(0, 2, 4));
    EXPECT_EQ(p1 - p2, point<float>(2, 2, 2));
    EXPECT_EQ(scalar_multiply(p1, p2), 2);
    EXPECT_EQ(vec_multiply(p1, p2), point<float>(2, -4, 2));
    EXPECT_EQ(p1 == p1, 1);
    EXPECT_EQ(p1 == p2, 0);
}

TEST(TestTriangleInter, TrgTest) {
    point<float> a1(1, 0, 0);
    point<float> a2(0, 1, 0);
    point<float> a3(0, 0, 0);

    std::vector<triangle<float>> atrg;
    atrg.emplace_back(a1, a2, a3);
    atrg.emplace_back(a1, a3, a2);
    atrg.emplace_back(a2, a1, a3);
    atrg.emplace_back(a2, a3, a1);
    atrg.emplace_back(a3, a1, a2);
    atrg.emplace_back(a3, a2, a1);

    point<float> b1(2, 1, 0);
    point<float> b2(3, 0, 0);
    point<float> b3(2, 0, 0);

    std::vector<triangle<float>> btrg;
    btrg.emplace_back(b1, b2, b3);
    btrg.emplace_back(b1, b3, b2);
    btrg.emplace_back(b2, b1, b3);
    btrg.emplace_back(b2, b3, b1);
    btrg.emplace_back(b3, b1, b2);
    btrg.emplace_back(b3, b2, b1);

    for (auto it = atrg.begin(); it != atrg.end(); ++it) {
        for (auto other = btrg.begin(); other != btrg.end(); ++other) {
            EXPECT_EQ(it->intersection(*other), 0);
        }
    }
}

TEST(TestLineConstr, TrgTest) {
    point<float> vec(1,2,3);
    point<float> point(4,5,6);

    line<float> line(vec, point);
    EXPECT_EQ(line.get_vec(), vec);
    EXPECT_EQ(line.get_point(), point);
}

TEST(TestLineEquality, TrgTest) {
    line<float> line1(point<float>(1,0,1), point<float>(0,0,0));
    line<float> line2(point<float>(1,0,1), point<float>(1,0,1));
    line<float> line3(point<float>(4,0,4), point<float>(-1,-1,-1));
    line<float> line4(point<float>(1,2,3), point<float>(4,5,6));

    EXPECT_EQ(line1 == line1, 1);
    EXPECT_EQ(line1 == line2, 1);
    EXPECT_EQ(line1 == line3, 0);
    EXPECT_EQ(line1 == line4, 0);
}

TEST(TestLineInter, TrgTest) {
    line<float> line1(point<float>(0,1,1), point<float>(0,0,0));
    line<float> line2(point<float>(1,0,1), point<float>(1,0,1));
    line<float> line3(point<float>(0,1,1), point<float>(0,0,0));
    line<float> line4(point<float>(0,1,1), point<float>(1,0,0));

    EXPECT_EQ(line1.intersection(line1).valid(), 0);
    EXPECT_EQ(line1.intersection(line2), point<float>(0,0,0));
    EXPECT_EQ(line1.intersection(line3).valid(), 0);
    EXPECT_EQ(line1.intersection(line4).valid(), 0);
}

TEST(TestPlaneEqual, TrgTest) {
    plane<float> p1(0, 0, 1, 2);
    plane<float> p2(0, 0, 2, 4);
    plane<float> p3(1, 2, 3, 4);

    EXPECT_EQ(p1 == p1, 1);
    EXPECT_EQ(p1 == p2, 1);
    EXPECT_EQ(p1 == p3, 0);
}

TEST(TestTriangle, TrgTest) {
    //points
    triangle<float> trg0 (1,1,1,1,1,1,1,1,1);
    triangle<float> trg1 (0,0,0,0,0,0,0,0,0);

    EXPECT_EQ(trg0.intersection(trg0), 1);
    EXPECT_EQ(trg0.intersection(trg1), 0);

    // lines
    triangle<float> trg2 (2, 2, 2, 2, 2, 2, 3, 3, 3);
    triangle<float> trg3 (2.5, 2.5, 2.5, 2, 2, 2, 3, 3, 3);
    triangle<float> trg4 (-1,-1,-1,0,0,0,0,0,0);
    triangle<float> trg5 (-1, -0.5, -1, -0.5, -0.5, -0.5, 0, -0.5, 0);

    EXPECT_EQ(trg2.intersection(trg3), 1);
    EXPECT_EQ(trg2.intersection(trg4), 0);
    EXPECT_EQ(trg4.intersection(trg5), 1);

    EXPECT_EQ(trg0.intersection(trg4), 0);
    EXPECT_EQ(trg1.intersection(trg4), 1);
    
    triangle<float> trg6(-10, 0, 0.5, 0, -10, 0.5, 0, 0, 0.5);
    triangle<float> trg7(-10, 0, 0, 0, -10, 0, 0, 0, 0);

    EXPECT_EQ(trg0.intersection(trg7), 0);
    EXPECT_EQ(trg1.intersection(trg7), 1);
    EXPECT_EQ(trg6.intersection(trg7), 0);

    triangle<float> trg8 (0,0,0,1,0,0,0,1,0);
    triangle<float> trg9 (0.1,0.1,5,0.3,0.3,5,0.2,0.2,-5);
    EXPECT_EQ(trg8.intersection(trg9), 1);

    triangle<float> trg10 (0,0,0,1,0,0,0,1,0);
    triangle<float> trg11 (0.1,0.1,-1,0.1,0.1,1,-10,0,0);
    EXPECT_EQ(trg10.intersection(trg11), 1);

    triangle<float> trg12 (1,1,0,3,1,0,1,3,0);
    triangle<float> trg13 (1,1,0,1,2,3,5,4,8);
    EXPECT_EQ(trg12.intersection(trg13), 1);

    triangle<float> trg14 (1,0,0,0,1,0,0,0,0);
    triangle<float> trg15 (0.5,0,0,0,-10,0,-10,-10,-10);
    EXPECT_EQ(trg14.intersection(trg15), 1);

    triangle<float> trg16 (1,0,0,0,1,0,0,0,1);
    triangle<float> trg17 (9,9,9,9,9,9,9,9,9);
    EXPECT_EQ(trg16.intersection(trg17), 0);

    triangle<float> trg18 (-3.584, 3.488, 0.3, 0.824, 2.268, 0.3, 0, -1.792, 0.3);
    triangle<float> trg19 (-1.792, 1.744, 0.3, 0.412, 1.134, 0.3, 0, -0.896, 0.3);
    EXPECT_EQ(trg18.intersection(trg19), 1);

    triangle<float> trg20 (408.6, -666.9, -721.3, 374.6, -660, -746.4, 372.3, -720.7, -782.5);
    triangle<float> trg21 (323, -647.3, -784.8, 467.5, -650.5, -726.3, 366.6, -766.3, -783.1);
    EXPECT_EQ(trg20.intersection(trg21), 1);

    triangle<float> trg22 (-705.3, 879.3, 547.2, -715.7, 874.9, 559.9, -712.1, 880.1, 558.2);
    triangle<float> trg23 (-702.7, 876.5, 551.7, -702.1, 889.6, 540.6, -713.6, 879.3, 543.8);
    EXPECT_EQ(trg22.intersection(trg23), 1);

    triangle<float> trg24 (126.149, 138.178, 171.904, 126.172, 137.917, 170.911, 125.882, 138.295, 171.045);
    triangle<float> trg25 (126.594, 138.351, 171.605, 125.963, 137.83, 171.136, 125.812, 137.839, 171.111);
    EXPECT_EQ(trg24.intersection(trg25), 1);
}
