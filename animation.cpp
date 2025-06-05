
#include "animation.h"
#include <sstream>
#include <iostream>

//folder is a path to the file
//filename - name of file
//frameCount - the number of frames that are include in folder
// frameTime - the time of one frame
//countStart - starting counting the files (every file has number at the end)
Animation::Animation(const std::string& folder, const std::string& filename, int frameCount, float frameTime, int countStart)
    : frameTime(frameTime), timer(0.0f), currentFrame(0)
{
    for(int i=0; i<frameCount; i++){
        std::stringstream ss;
        ss<<folder<<"/"<<filename<<(i+countStart)<<".png"; //Creating a string stream that stores the path and filename

        auto tex=std::make_shared<sf::Texture>();
        if (!tex->loadFromFile(ss.str())){ //Trying to load the file that includes texture frame
            continue;
        }
        //Setting textures to sprite
        sf::Sprite sprite;
        sprite.setTexture(*tex);

        textures.push_back(tex);
        frames.push_back(sprite);
    }

    if (frames.empty()) {
        std::cerr << "Cannot loaded animation frames!!!\n";
    }
}

void Animation::update(float dt) {
    if(frames.empty())
        return;
    //Changing frames when timer is longer than time of one frame
    timer += dt;
    if (timer>= frameTime) {
        timer =0.0f;
        currentFrame=(currentFrame+1)%frames.size();
    }
}

//Every frame in one position
void Animation::setPosition(float x, float y){
    for(auto& frame : frames){
        frame.setPosition(x, y);
    }
}

void Animation::draw(sf::RenderWindow& window) {
    if (!frames.empty())
        window.draw(frames[currentFrame]);
}
//Setting scale of sprite
void Animation::setScale(float x, float y) {
    for (auto& frame : frames) {
        frame.setScale(x, y);
    }
}

sf::FloatRect Animation::getGlobalBounds() const {
    if (!frames.empty())
        return frames[currentFrame].getGlobalBounds();
    return sf::FloatRect();
}



