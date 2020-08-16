#include "../echo.h"
#include <iostream>
#include <ncurses.h>
using namespace std;

static void hello(CORBA::Object_ptr obj)
{
  Echo_var e = Echo::_narrow(obj);
  if (CORBA::is_nil(e)) {
    cerr << "cannot invoke on a nil object reference."
    << endl;
    return;
  }
  bool inputGood = false;
  char symbol = 0;
  initscr();

  do{
      cbreak();
      symbol = getch();
      if (symbol == ' ') break;
      else if(symbol == '\n') std::cout << std::endl;
      inputGood = e->echoChar(symbol);
  }
  while(inputGood);

  endwin();
}

int main(int argc, char** argv)
{
  try {
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    if (argc != 2) {
      cerr << "Usage: client <object reference>" << endl;
      return 1;
    }

    CORBA::Object_var obj = orb->string_to_object(argv[1]);

    Echo_var echoref = Echo::_narrow(obj);

    if (CORBA::is_nil(echoref)) {
      cerr << "Can't narrow reference." << endl;
      return 1;
    }

    hello(echoref);
    orb->destroy();
  }
  catch (CORBA::TRANSIENT&) {
    cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "server." << endl;
  }
  catch (CORBA::SystemException& ex) {
    cerr << "Caught a CORBA::" << ex._name() << endl;
  }
  catch (CORBA::Exception& ex) {
    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
  }
  return 0;
}
