/*
 * File: humanpyramid.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file implements the human pyramid function for Homework 3.
 */


#include <bits/stdc++.h>
#include "humanpyramid.h"
#include <iostream>
#include "map.h"

using namespace std;

/**
 * Given a human pyramid in which each person weighs exactly 200 pounds,
 * returns the weight on the back of the person at the specified row and
 * column in the human pyramid. Rows and columns are zero-indexed, so,
 * for example, weightOnBackOf(2, 0) would give the weight on the back of
 * the leftmost person in the third row of the pyramid.
 *
 * @param row The zero-indexed row of the person in the pyramid.
 * @param col The zero-indexed column of the person in the pyramid.
 * @return The weight on the back of that person.
 */

double weightOnBackOf(int row, int col) {
    static Map<pair<int, int>, double> mp;
    pair<int, int> p(row, col);
    if(row == 0) {
        return 0;
    } else {
        if(mp.containsKey(p)) {
            return mp[p];
        } else {
            if(col == 0 || col == row) {
                double ans= 100 + 0.5 * weightOnBackOf(row - 1, 0);
                mp[p] = ans;
                return ans;
            } else {
                double ans= 200 + 0.5 * weightOnBackOf(row - 1, col) + 0.5 * weightOnBackOf(row - 1, col - 1);
                mp[p] = ans;
                return ans;
            }
        }
    }
}
