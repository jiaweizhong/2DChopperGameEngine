#ifndef ANIMATION_H
#define ANIMATION_H
class Animation
{
private:
    /* data */
public:
    unsigned int index;
    unsigned int numFrames;
    unsigned int animationSpeed;
    Animation(/* args */){};
    Animation(int index, int numFrames, int speed);

    ~Animation(){};
};

#endif