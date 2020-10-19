#include "Font.h"

Font::Font(char *path,char* texturePath) {
    this->path = path;
    this->atlas = new Texture(texturePath);
    this->atlas->load(true);
    this->fontImageSize = (float)atlas->getWidth();
    read();
    std::map<char, Character *>::iterator it;
    for (it = characters.begin(); it != characters.end(); it++) {
        if(it->second->getHeight() > highestCharacter){
            highestCharacter = it->second->getHeight();
        }
    }
}

void Font::read() {
    std::ifstream stream(path);
    std::string line;
    if(stream.is_open()) {
        while (std::getline(stream, line)) {
            if(line.find("size=") != std::string::npos){
                int index = line.find("size=");
                int indexEnd = line.find("bold=");
                index+= 5;
                fontSize = std::stoi(line.substr(index,indexEnd - index));
            }
            if(line.find("char id") != std::string::npos){
                int idindex = line.find("id=") + 3;
                int xindex = line.find("x=") + 2;
                int yindex = line.find("y=") + 2;
                int widthindex = line.find("width=") + 6;
                int heightindex = line.find("height=") + 7;
                int xoffsetindex = line.find("xoffset=") + 8;
                int yoffsetindex = line.find("yoffset=") + 8;
                int xadvanceindex = line.find("xadvance=") + 9;
                int pageindex = line.find("page=") + 5;

                idindex = std::stoi(line.substr(idindex,xindex - idindex - 2));
                xindex = std::stoi(line.substr(xindex,yindex - xindex - 1));
                yindex = std::stoi(line.substr(yindex,widthindex - yindex - 1));
                widthindex = std::stoi(line.substr(widthindex,heightindex - widthindex - 5));
                heightindex = std::stoi(line.substr(heightindex,xoffsetindex - heightindex - 6));
                xoffsetindex = std::stoi(line.substr(xoffsetindex,yoffsetindex - xoffsetindex - 7));
                yoffsetindex = std::stoi(line.substr(yoffsetindex,xadvanceindex - yoffsetindex - 8));
                xadvanceindex = std::stoi(line.substr(xadvanceindex,pageindex - xadvanceindex - 8));
                auto character = new Character(idindex, xindex, yindex, widthindex, heightindex, xoffsetindex, yoffsetindex, xadvanceindex);
                if(idindex == ' '){
                    space_width = character->getXadvance();
                }
                characters.insert(std::pair<char,Character*>(char (idindex), character));
            }
        }
    }else{
        failedToLoad = true;
    }
}

Character* Font::getCharacter(char key) {
    return characters.at(key);
}

std::string Font::getErrorMessage() {
    std::string result;
    result.append(path);
    if(failedToLoad)
        result.append("Failed to load Font");
    else
        result.append("Successfully loaded Font");
    return result;
}
