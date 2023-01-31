
struct ClientTable {
    char cClientID;
    char cSelfID;
    int iSocketFD;
    char* pcId;
    int iSocketFd;
    char* pcFriendId;
};

struct IDHeader {
    char selfID;
    char clientID;
};