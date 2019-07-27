#ifndef CLIENTREACTOR_H
#define CLIENTREACTOR_H


class ClientReactor
{
    public:
        ClientReactor(int nClientFd);
        virtual ~ClientReactor();

        void BeginRoutine();

        int m_nClientFd;
    protected:
    private:
};

#endif // CLIENTREACTOR_H
