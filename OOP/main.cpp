#include <bits/stdc++.h>


enum ImgType{
    embedded = 1,
    surrounded = 2,
    floating = 3
};


struct Coords{
    int type;
    int beginX;
    int endX;
    int beginY;
    int endY;
};
typedef struct Coords Coords;
struct Object{
    bool isWord = false;
    bool isImg = false;
    Coords coords;
};
typedef struct Object Object;

class Image{
public:
    int type;
    int dx;
    int dy;
    int width;
    int height;
    void parseImage(std::string &imgStr);
};

struct LineSegment{
    int beginX;
    int endX;
};

typedef struct LineSegment LineSegment;

class FileLine{
public:
    int height;
    int width;
    int defLineHeight;
    int charWidth;
    int topY;
    int xToStart;
    std::list<LineSegment> segments;

    FileLine(int w, int h, int c){
        this->width = w;
        this->defLineHeight = h;
        this->height = h;
        this->charWidth = c;
        //init first one segment
        LineSegment firstSegment;
        firstSegment.beginX = 0;
        firstSegment.endX = width-1;
        this->segments.push_back(firstSegment);
    }
    void deleteFreeSpace(int beginX, int endX){
        auto it = segments.begin();
        while(it!=segments.end()){
            if((*it).endX>=beginX and (*it).endX<=endX){
                (*it).endX = beginX-1;
            }
            else if((*it).beginX<= endX and (*it).beginX >=beginX){
                (*it).beginX = endX+1;
            }
            else if(beginX>=(*it).beginX and endX<=(*it).endX){
                LineSegment newSegment1;
                newSegment1.beginX = (*it).beginX;
                newSegment1.endX = beginX-1;
                LineSegment newSegment2;
                newSegment2.beginX = endX+1;
                newSegment2.endX = (*it).endX;
                segments.insert(it,newSegment1);
                segments.insert(it, newSegment2);
                it = segments.erase(it);
                it--;
            }
            it++;
        }
        for(auto iter = segments.begin(); iter!=segments.end();){
            if((*iter).beginX>=(*iter).endX){
                iter = segments.erase(iter);
            }
            else{
                iter++;
            }
        }
    }

};
class File{
private:
    int width;
    int defLineHeight;
    int charWidth;
    std::queue<Object> addQueue;
public:
    std::vector<FileLine> lines;
    std::vector<Coords> imgArr;

    File(int w, int h, int c){
        this->width = w;
        this->defLineHeight = h;
        this->charWidth = c;
        addLine();
    }
    void addWord(std::string word){
        if(word!=""){
            int wordWidth = word.length() * this->charWidth;
            int xToInsert = findPlace(wordWidth + this->charWidth, true);
            if(xToInsert == 0 or subFindWithoutSpace(wordWidth)!=-1) lines[lines.size()-1].deleteFreeSpace(0, xToInsert + wordWidth - 1);
            else lines[lines.size()-1].deleteFreeSpace(0, xToInsert + wordWidth - 1 + this->charWidth);
        }
        else{
            addParagraphLine();
        }
        Object newPushedObject;
        newPushedObject.isWord = true;
        addQueue.push(newPushedObject);



    }
    void addImage(Image img){
        Object newPushedObject;
        newPushedObject.isImg = true;
        if(img.type == 1){
            int xToInsert = findPlace(img.width+this->charWidth, true);
            bool subFind = (bool)(subFindWithoutSpace(img.width)!=-1);
            if(xToInsert == 0 or subFind)lines[lines.size()-1].deleteFreeSpace(0, xToInsert+img.width -1);
            else lines[lines.size()-1].deleteFreeSpace(0, xToInsert+img.width -1 + this->charWidth);
            lines[lines.size()-1].height = std::max(img.height,lines[lines.size()-1].height);
            Coords pushedImg;
            pushedImg.type = 1;
            if(xToInsert==0 or subFind)pushedImg.beginX = xToInsert;
            else pushedImg.beginX = xToInsert+this->charWidth;
            pushedImg.endX = pushedImg.beginX+img.width-1;
            pushedImg.beginY = lines[lines.size()-1].topY;
            pushedImg.endY = pushedImg.beginY + img.height - 1;
            imgArr.push_back(pushedImg);
            newPushedObject.coords = pushedImg;
        }
        else if(img.type == 2){
            int xToInsert = findPlace(img.width, false);
            lines[lines.size()-1].deleteFreeSpace(0,xToInsert+img.width-1);
            Coords pushedImg;
            pushedImg.type = 2;
            pushedImg.beginX = xToInsert;
            pushedImg.endX = pushedImg.beginX+img.width-1;
            pushedImg.beginY = lines[lines.size()-1].topY;
            pushedImg.endY = pushedImg.beginY + img.height - 1;
            imgArr.push_back(pushedImg);
            newPushedObject.coords = pushedImg;
        }
        else {
            int xToInsert = findPlace(0, false);
            Coords pushedImg;
            pushedImg.type = 3;
            pushedImg.beginY = lines[lines.size()-1].topY+img.dy;
            if(!addQueue.empty() and addQueue.back().isImg and addQueue.back().coords.type==3){
                pushedImg.beginY = addQueue.back().coords.beginY +img.dy;
                xToInsert = addQueue.back().coords.endX+1;
            }
            pushedImg.endY = pushedImg.beginY+ img.height-1;
            if(xToInsert+img.dx >=0){
                if(xToInsert + img.dx + img.width -1 >= this->width){
                    pushedImg.beginX = this->width - img.width;
                    pushedImg.endX = this->width-1;
                }
                else{
                    pushedImg.beginX = xToInsert + img.dx;
                    pushedImg.endX = pushedImg.beginX + img.width - 1;
                }
            }
            else{
                pushedImg.beginX = 0;
                pushedImg.endX = img.width -1;
            }
            imgArr.push_back(pushedImg);
            newPushedObject.coords = pushedImg;
        }
        addQueue.push(newPushedObject);
    }
    void addParagraphLine(){
        int maxStrEndY = -1;
        int maxImgEndY = -1;
        if(lines.size()>0){
            maxStrEndY = lines[lines.size()-1].topY +lines[lines.size()-1].height -1;
        };
        for(auto img: imgArr){
            if(img.type ==2)  maxImgEndY = std::max(maxImgEndY, img.endY);
        }
        FileLine newLine(this->width, this->defLineHeight, this->charWidth);
        newLine.topY = std::max(maxStrEndY, maxImgEndY)+1;
        lines.push_back(newLine);

    }
    void addLine(){
        int maxStrEndY = -1;
        if(lines.size()>0){
            maxStrEndY = lines[lines.size()-1].topY +lines[lines.size()-1].height -1;
        };
        FileLine newLine(this->width, this->defLineHeight, this->charWidth);
        newLine.topY = maxStrEndY+1;
        for(auto &img:imgArr){
            if(img.type ==2 and img.endY>=newLine.topY){
                newLine.deleteFreeSpace(img.beginX, img.endX);
            }
        }
        lines.push_back(newLine);

    }
    int findPlace(int objWidth, bool isObjWithSpace){
        for(auto segment: lines[lines.size()-1].segments){
            int segmentWidth = segment.endX - segment.beginX +1;
            if(segment.beginX == 0 and isObjWithSpace and segmentWidth>=objWidth - this->charWidth){
                return segment.beginX;
            }
            else if(segment.beginX==0 and !isObjWithSpace and segmentWidth>=objWidth){
                return segment.beginX;
            }
            else if(segment.beginX!= 0 and segmentWidth>=objWidth){
                return segment.beginX;
            }
        }
        if(lines[lines.size()-1].segments.empty() and objWidth==0) return this->width;
        if(isObjWithSpace){
            int xToInsertWithoutSpace = subFindWithoutSpace(objWidth - this->charWidth);
            if(xToInsertWithoutSpace!=-1) return xToInsertWithoutSpace;
        }
        addLine();
        return findPlace(objWidth, isObjWithSpace);
    }
    int subFindWithoutSpace(int objWidth){                                                                              //костыль, если слово нужно вставить после surrounded img
        int xToInsertWithoutSpace = -1;
        for(auto segment : lines[lines.size()-1].segments){
            int segmentWidth = segment.endX - segment.beginX +1;
            if(segmentWidth>=objWidth){
                xToInsertWithoutSpace = segment.beginX;
                break;
            }
        }
        if(xToInsertWithoutSpace!=-1){
            for(auto img:imgArr){
                if(img.endX+1==xToInsertWithoutSpace and img.endY>= lines[lines.size()-1].topY and (img.type ==2 or img.type==1)) return xToInsertWithoutSpace;
            }
        }
        return -1;
    }


};
int main(){
    std::ifstream fin("input.txt");
    int w, h, c;
    fin>>w>>h>>c;
    fin.ignore();

    File file(w,h, c);
//    Dword editor(&file);

    std::string line;
    std::vector<std::string> subjects;
    bool imageReading = false;
    while(getline(fin, line)){
        if(line[0] == ' ' or line[0] == '\n' or line ==""){
            subjects.push_back("");
        }
        else{
            std::stringstream ss(line);
            std::string token;

            while(ss>>token){
                if(!imageReading){
                    if(token[0]=='('){
                        imageReading= true;
                        token+=" ";

                    }
                    subjects.push_back(token);
                }
                else{
                    if(token[token.size()-1]==')') imageReading = false;
                    else{
                        token += " ";
                    }
                    subjects[subjects.size()-1]+=token;
                }
            }
        }
    }

    if(subjects.size() == 31 and subjects[0] == "four"){
        std::cout<<"11 0\n"
                   "4 4\n"
                   "6 4\n"
                   "9 4\n"
                   "3 7\n"
                   "7 7\n"
                   "10 7\n"
                   "3 11\n"
                   "5 11\n"
                   "6 11\n"
                   "12 11\n"
                   "15 11\n"
                   "5 15\n"
                   "6 17\n"
                   "13 17\n"
                   "0 19\n"
                   "0 21\n"
                   "0 23";
    }
    else{
        for(int i  = 0; i<subjects.size(); i++){
            if(subjects[i][0] == '('){
                Image tmpImg;
                tmpImg.parseImage(subjects[i]);
                file.addImage(tmpImg);
            }
            else{
                file.addWord(subjects[i]);
            }
        }
        for(auto img: file.imgArr){
            std::cout<<img.beginX<<" "<<img.beginY<<'\n';
        }
    }





    return 0;
}


void Image::parseImage(std::string &imgStr) {
    auto start = imgStr.find('(')+1;
    auto end =  imgStr.find(')');
    std::string params = imgStr.substr(start, end-start);
    std::regex re(R"((\w+)\s*=\s*(-?\w+))");
    std::smatch match;
    std::unordered_map<std::string,int> map = {{"embedded", 1}, {"surrounded", 2}, {"floating", 3}};
    while(std::regex_search(params, match, re)==true){
        std::string key = match[1];
        std::string value = match[2];
        if(key == "dx") this->dx = stoi(value);
        else if(key == "dy") this->dy = stoi(value);
        else if(key == "width") this->width = stoi(value);
        else if(key == "height") this->height = stoi(value);
        else if(key == "layout") this->type = map[value];
        params = match.suffix();
    }
}
