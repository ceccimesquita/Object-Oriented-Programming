/*
fiz a questão sozinha com o esqueleto q tinha no replit 
*/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fn.hpp>
using namespace fn;

class Time {
private:
    int hour{0}, minute{0}, second{0};
public:
    Time(int hour, int minute ,int second) {
      setHour(hour);
      setMinute(minute);
      setSecond(second);
    }
    void setHour(int hour) {
      if (hour >= 0 && hour <= 23){
        this->hour = hour;
        return;
      }
      write("fail: hora invalida");
    }
    void setMinute(int minute) {
      if (minute >= 0 && minute < 60){
        this->minute = minute;
        return;
      }
      write("fail: minuto invalido");
    }
    void setSecond(int second) {
      if(second >= 0 && second < 60){
        this->second = second;  
        return;
      }
      write("fail: segundo invalido");
    }
    int getHour() {
        return {}; // todo
    }
    int getMinute() {
        return {}; // todo
    }
    int getSecond() {
        return {}; // todo
    }
    void nextSecond() {
      if(second < 59){
        second++;
        setSecond(second);
        return;
      }
      if(second == 59 && minute > 59){
        second = 00;
        minute++;
        setMinute(minute);
        return;
      }
      if(second ==  59 && minute == 59 && hour < 23){
        second = 00;
        minute = 00;
        hour++;
        setHour(hour);
        return;
      }
      if(second ==  59 && minute == 59 && hour == 23){
        second = 00;
        minute = 00;
        hour = 00;
        return;
      }

      
    }
    std::string str() {
        return fn::format("{%02d}:{%02d}:{%02d}", hour, minute, second);
    }
};

int main() {
    Time time(0, 0, 0);
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');

        write("$" + line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "set") {
            time.setHour(+args[1]);
            time.setMinute(+args[2]);
            time.setSecond(+args[3]);
        } else if (args[0] == "init") {
             time = Time(+args[1], +args[2], +args[3]);
        } else if (args[0] == "show") {
            fn::write(time.str());
        } else if (args[0] == "next") {
            time.nextSecond();
        } else {
            fn::write("fail: comando invalido");
        }
    }
}