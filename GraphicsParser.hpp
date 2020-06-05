#ifndef GRAPHICS_PARSER_HPP
#define GRAPHICS_PARSER_HPP
#include "Vector.hpp"
#include "Session.hpp"

class GraphicsParser {
private:
    int current_max_id;
    Session* current_session;
    Vector<Session> sessions;
public:
    GraphicsParser();
    void switch_session(int session_id);
    void run();
    void load(String command);
    void close();
    void help();
};

#endif