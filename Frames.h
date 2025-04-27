#pragma once
#include <list>
#include <iterator>
#include <iostream>
class Frame {
protected:
    int score = 0;
public:
    Frame() { }
    virtual void scores(int bowl1, int bowl2) {}
    virtual int returnscore() { return 0; }
    virtual void addextrascore(int bowl1) {
        return;
    }
    virtual void addextrascore(int bowl1, int bowl2) {
        return;
    }
};

class NormalFrame :public Frame {
public:
    void scores(int bowl1, int bowl2) {
        score = bowl1 + bowl2;
    }
    int returnscore() { return score; }
};

class SpareFrame :public Frame {
public:
    void scores(int bowl1, int bowl2) {
        score = 10;
    }
    int returnscore() { return score; }
    void addextrascore(int bowl1) {
        score += bowl1;
    }
};

class StrikeFrame :public Frame {
public:
    void scores(int bowl1, int bowl2) {
        score = 10;
    }
    int returnscore() { return score; }
    void addextrascore(int bowl1, int bowl2 = 0) {
        score += bowl1 + bowl2;
    }
};

class FrameType {
public:
    static std::unique_ptr<Frame> decideFrameType(const int& score1, const int& score2) {
        if (score1 == 10) {
            std::unique_ptr<Frame> frame = std::make_unique<StrikeFrame>();
            frame->scores(score1, score2);
            return frame;
        }
        else if (score1 + score2 == 10) {
            std::unique_ptr<Frame> frame = std::make_unique<SpareFrame>();
            frame->scores(score1, score2);
            return frame;
        }
        else {
            std::unique_ptr<Frame> frame = std::make_unique<NormalFrame>();
            frame->scores(score1, score2);
            return frame;
        }
    }
};