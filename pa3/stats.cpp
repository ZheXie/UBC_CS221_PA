#include "stats.h"

#include "stats.h"

stats::stats(PNG &im){
    /* Your code here!! */
    sumRed.resize(im.width());
    sumGreen.resize(im.width());
    sumBlue.resize(im.width());
    sumsqRed.resize(im.width());
    sumsqGreen.resize(im.width());
    sumsqBlue.resize(im.width());
    for (int i = 0; i < im.width(); i++) {
        sumRed[i].resize(im.height());
        sumGreen[i].resize(im.height());
        sumBlue[i].resize(im.height());
        sumsqRed[i].resize(im.height());
        sumsqGreen[i].resize(im.height());
        sumsqBlue[i].resize(im.height());
    }
    for (int i = 0; i < im.width(); i++) {
        for (int j = 0; j < im.height(); j++) {
            RGBAPixel * curr = im.getPixel(i, j);

            if (i == 0 && j == 0) {
                sumRed[i][j] = curr->r;
                sumGreen[i][j] = curr->g;
                sumBlue[i][j] = curr->b;
                sumsqRed[i][j] = (curr->r) * (curr->r);
                sumsqGreen[i][j] = (curr->g) * (curr->g);
                sumsqBlue[i][j] = (curr->b) * (curr->b);
            } else if (i == 0 && j != 0) {
                sumRed[i][j] = curr->r + sumRed[i][j - 1];
                sumGreen[i][j] = curr->g + sumGreen[i][j - 1];
                sumBlue[i][j] = curr->b + sumBlue[i][j - 1];
                sumsqRed[i][j] = (curr->r) * (curr->r) + sumsqRed[i][j - 1];
                sumsqGreen[i][j] = (curr->g) * (curr->g) + sumsqGreen[i][j - 1];
                sumsqBlue[i][j] = (curr->b) * (curr->b) + sumsqBlue[i][j - 1];
            } else if (i != 0 && j == 0) {
                sumRed[i][j] = curr->r + sumRed[i - 1][j];
                sumGreen[i][j] = curr->g + sumGreen[i - 1][j];
                sumBlue[i][j] = curr->b + sumBlue[i - 1][j];
                sumsqRed[i][j] = (curr->r) * (curr->r) + sumsqRed[i - 1][j];
                sumsqGreen[i][j] = (curr->g) * (curr->g) + sumsqGreen[i - 1][j];
                sumsqBlue[i][j] = (curr->b) * (curr->b) + sumsqBlue[i - 1][j];
            } else {
                sumRed[i][j] = curr->r + sumRed[i - 1][j] + sumRed[i][j - 1] - sumRed[i - 1][j - 1];
                sumGreen[i][j] = curr->g + sumGreen[i - 1][j] + sumGreen[i][j - 1] - sumGreen[i - 1][j - 1];
                sumBlue[i][j] = curr->b + sumBlue[i - 1][j] + sumBlue[i][j - 1] - sumBlue[i - 1][j - 1];
                sumsqRed[i][j] = (curr->r) * (curr->r) + sumsqRed[i - 1][j] + sumsqRed[i][j - 1] - sumsqRed[i - 1][j - 1];
                sumsqGreen[i][j] = (curr->g) * (curr->g) + sumsqGreen[i - 1][j] + sumsqGreen[i][j - 1] - sumsqGreen[i - 1][j - 1];
                sumsqBlue[i][j] = (curr->b) * (curr->b) + sumsqBlue[i - 1][j] + sumsqBlue[i][j - 1] - sumsqBlue[i - 1][j - 1];
            }
        }
    }
}

long stats::getSum(char channel, pair<int, int> ul, int w, int h){
    /* Your code here!! */
    vector< vector< long >> * sumChannel;
    if (channel == 'r') sumChannel = &sumRed;
    if (channel == 'g') sumChannel = &sumGreen;
    if (channel == 'b') sumChannel = &sumBlue;
    if (ul.first == 0 && ul.second == 0) {
         return (*sumChannel)[ul.first + w - 1][ul.second + h - 1];
    } else if (ul.first == 0) {
         return (*sumChannel)[ul.first + w - 1][ul.second + h - 1] - (*sumChannel)[ul.first + w - 1][ul.second - 1];
    } else if (ul.second == 0) {
         return (*sumChannel)[ul.first + w - 1][ul.second + h - 1] - (*sumChannel)[ul.first - 1][ul.second + h - 1];
    } else {
         return (*sumChannel)[ul.first + w - 1][ul.second + h - 1] - (*sumChannel)[ul.first - 1][ul.second + h - 1] -(*sumChannel)[ul.first + w - 1][ul.second - 1] + (*sumChannel)[ul.first - 1][ul.second - 1];
    }
}

long stats::getSumSq(char channel, pair<int, int> ul, int w, int h){
    /* Your code here!! */
    vector< vector< long >> * sumsqChannel;
    if (channel == 'r') sumsqChannel = &sumsqRed;
    if (channel == 'g') sumsqChannel = &sumsqGreen;
    if (channel == 'b') sumsqChannel = &sumsqBlue;
    if (ul.first == 0 && ul.second == 0) {
         return (*sumsqChannel)[ul.first + w - 1][ul.second + h - 1];
    } else if (ul.first == 0) {
         return (*sumsqChannel)[ul.first + w - 1][ul.second + h - 1] - (*sumsqChannel)[ul.first + w - 1][ul.second - 1];
    } else if (ul.second == 0) {
         return (*sumsqChannel)[ul.first + w - 1][ul.second + h - 1] - (*sumsqChannel)[ul.first - 1][ul.second + h - 1];
    } else {
         return (*sumsqChannel)[ul.first + w - 1][ul.second + h - 1] - (*sumsqChannel)[ul.first - 1][ul.second + h - 1] -(*sumsqChannel)[ul.first + w - 1][ul.second - 1] + (*sumsqChannel)[ul.first - 1][ul.second - 1];
    }
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int w, int h){
    /* Your code here!! */
    double sumR = getSum('r', ul, w, h);
    double sumG = getSum('g', ul, w, h);
    double sumB = getSum('b', ul, w, h);
    double avgR = sumR * sumR / (w * h);
    double avgG = sumG * sumG / (w * h);
    double avgB = sumB * sumB / (w * h);
    double varR = getSumSq('r', ul, w, h) - avgR;
    double varG = getSumSq('g', ul, w, h) - avgG;
    double varB = getSumSq('b', ul, w, h) - avgB;
    return varR + varG + varB;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int w, int h){
    /* Your code here!! */
    double sumR = getSum('r', ul, w, h);
    double sumG = getSum('g', ul, w, h);
    double sumB = getSum('b', ul, w, h);
    double avgR = sumR / (w * h);
    double avgG = sumG / (w * h);
    double avgB = sumB / (w * h);
    RGBAPixel avg(avgR, avgG, avgB);
    return avg;
}
