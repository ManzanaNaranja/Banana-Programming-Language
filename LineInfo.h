#ifndef LINEINFO__H
#define LINEINFO__H

class LineInfo {
    public:
      int goto_line;
      LineInfo(int line=0) : goto_line(line) {}
};

#endif