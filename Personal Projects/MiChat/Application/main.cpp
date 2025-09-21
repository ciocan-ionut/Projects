#include "Tests.h"
#include "ChatRepository.h"
#include "ChatService.h"
#include "LoginWindow.h"
#include "SignUpWindow.h"
#include "MainWindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Tests::runTests();

    QApplication app(argc, argv);

    ChatRepository chatRepository;

    ChatService chatService{ chatRepository };

    MainWindow* mainWindow = new MainWindow{ chatService };

    SignUpWindow* signUpWindow = new SignUpWindow{ chatService };

    LoginWindow* loginWindow = new LoginWindow{ chatService };

    loginWindow->setupWindows(mainWindow, signUpWindow);
    signUpWindow->setupWindows(mainWindow, loginWindow);
    mainWindow->setupWindows(loginWindow);

    loginWindow->show();

    return app.exec();
}
