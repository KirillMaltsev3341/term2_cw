#include "Output.h"
#include "Handler.h"


int main(int argc, char **argv)
{
    Output::showAuthorInfo("5.17", "Kirill", "Maltsev");
    hdlr::Handler handler;
    handler.getFlags(argc, argv);
    handler.handleFlags();
    return 0;
}