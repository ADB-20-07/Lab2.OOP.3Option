#include <iostream>
#include <string>

// ������������ ���������� �����������
const int MAX_OBSERVERS = 3;

// ����������� ����� ��� �����������
class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

// ���������� ����� ��� ���������� �� ������������� �������
class EconomicObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Economic news: " << message << std::endl;
    }
};

// ���������� ����� ��� ���������� �� ������� ������
class SportObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Sport news: " << message << std::endl;
    }
};

// ���������� ����� ��� ���������� �� ���������� ������� ������
class CulturalObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Cultural news: " << message << std::endl;
    }
};

// ���������� ����� ��� ���������� �� ������� ����� � ����������������
class ScienceObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Science and programming news: " << message << std::endl;
    }
};

// ����������� ����� ��� ��������
class Publisher {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify(const std::string& message) = 0;
};

// ���������� ����� ��� ��������
class EmailPublisher : public Publisher {
private:
    Observer* observers[MAX_OBSERVERS];
    int count = 0;
public:
    void attach(Observer* observer) override {
        if (count < MAX_OBSERVERS) {
            observers[count++] = observer;
        }
    }
    void detach(Observer* observer) override {
        for (int i = 0; i < count; i++) {
            if (observers[i] == observer) {
                for (int j = i; j < count - 1; j++) {
                    observers[j] = observers[j + 1];
                }
                count--;
                break;
            }
        }
    }
    void notify(const std::string& message) override {
        for (int i = 0; i < count; i++) {
            observers[i]->update(message);
        }
    }
};
int main() {
    // ������� ��������
    EmailPublisher publisher;

    // ������� �����������
    EconomicObserver economicObserver;
    SportObserver sportObserver;
    CulturalObserver culturalObserver;
    ScienceObserver scienceObserver;

    // ����������� ����������� �� ��������
    publisher.attach(&economicObserver);
    publisher.attach(&sportObserver);
    publisher.attach(&culturalObserver);
    publisher.attach(&scienceObserver);

    // ��������� �������
    publisher.notify("New economic report!");
    publisher.notify("New sports results!");
    publisher.notify("New cultural event!");
    publisher.notify("New science discovery!");

    std::cout << std::endl;
    // ���������� ���������� �� ��������
    publisher.detach(&economicObserver);
    std::cout << "Economical Observer detach " << std::endl;
    // ��������� ������� �����
    std::cout << std::endl;
    
    publisher.notify("Another new economic report!");
    publisher.notify("Another new sports results!");
    publisher.notify("Another new cultural event!");
    publisher.notify("Another new science discovery!");

    return 0;
}