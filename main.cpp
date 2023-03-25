#include <iostream>
#include <cassert>
#include <vector>
#include <string>

const int PERSON_COUNT = 12;
const int DEVICE_COUNT = 7;

enum class RowType { FIRST, SECOND };
enum class OpType { ADD, SUBTRACT };
enum class DeviceType { FORK, SPOON, KNIFE, PLATE, CHAIR, VIP_SPOON, VIP_PLATE };

void printInfo(int (&arr)[PERSON_COUNT][DEVICE_COUNT], const std::string &title = "") {
    std::string devicesTitle[DEVICE_COUNT] = {
            "    FORK   ",
            "   SPOON   ",
            "   KNIFE   ",
            "   PLATE   ",
            "   CHAIR   ",
            "VIP_SPOON ",
            "VIP_PLATE "
    };

    std::cout << "\t\t----------- " << title << " -------------" << std::endl;
    for (const auto &item : devicesTitle) std::cout << " " << item;
    std::cout << std::endl;

    for (int i = 0; i < PERSON_COUNT; ++i) {
        std::cout << i << (i < 10 ? ": " : ":");

        for (int flat : arr[i]) std::cout << "     " << flat << "      ";

        std::cout << std::endl;
    }
}

// возвращает место в одномерном массиве
int getSeatNumber(RowType row, int place) {
    const int SEATS_ALONG_ONE_SIDE = PERSON_COUNT / 2;
    assert(place > 0 && place <= SEATS_ALONG_ONE_SIDE);

    return static_cast<int>(row) * SEATS_ALONG_ONE_SIDE + (place - 1);
}

void changeDeviceSet(int (&arr)[PERSON_COUNT][DEVICE_COUNT], int seat, OpType op, DeviceType device, int deviceCount = 1) {
    switch (op) {
        case OpType::ADD:
            arr[seat][static_cast<int>(device)] += deviceCount;
            break;
        case OpType::SUBTRACT:
            int result =  arr[seat][static_cast<int>(device)] - deviceCount;
            arr[seat][(int)device] = result > 0 ? result : 0;
            // Но можно и вызвать предупреждение:
            // assert(result >= 0);
            break;
    }
}

int main() {
    const int FIRST_VIP = 0;
    int seatNumber = 0;
    std::string title;

    int personList[PERSON_COUNT][DEVICE_COUNT] = {
            { 1, 1, 1, 2, 1, 1, 1 },
            { 1, 1, 1, 2, 1, 1, 1 },
            { 1, 1, 1, 2, 1, 0, 0 },
            { 1, 1, 1, 2, 1, 0, 0 },
            { 1, 1, 1, 2, 1, 0, 0 },
            { 1, 1, 1, 2, 1, 0, 0 },
            { 1, 1, 1, 2, 1, 0, 0 },
            { 1, 1, 1, 2, 1, 0, 0 },
            { 1, 1, 1, 2, 1, 0, 0 },
            { 1, 1, 1, 2, 1, 0, 0 },
            { 1, 1, 1, 2, 1, 0, 0 },
            { 1, 1, 1, 2, 1, 0, 0 },
    };

    printInfo(personList, "starting position of guests");

    // Первый ряд, пятое место
    seatNumber = getSeatNumber(RowType::FIRST, 5);
    // Добавили стул
    changeDeviceSet(personList, seatNumber, OpType::ADD, DeviceType::CHAIR);
    title = std::to_string(seatNumber) + ": received chair";
    printInfo(personList, title);

    // Второй ряд, третье место
    seatNumber = getSeatNumber(RowType::SECOND, 3);
    // Украдена ложка
    changeDeviceSet(personList, seatNumber, OpType::SUBTRACT, DeviceType::SPOON);
    title = std::to_string(seatNumber) + ": his spoon was stolen";
    printInfo(personList, title);

    // Первая вип-персона
    // Поделилась ложкой
    changeDeviceSet(personList, FIRST_VIP, OpType::SUBTRACT, DeviceType::SPOON);
    title = std::to_string(FIRST_VIP) + ": he shared a spoon";
    printInfo(personList, title);

    // Второй ряд, третье место
    // Ложка добавлена
    changeDeviceSet(personList, seatNumber, OpType::ADD, DeviceType::SPOON);
    title = std::to_string(seatNumber) + ": received spoon";
    printInfo(personList, title);

    // Первая вип-персона
    // Забрали десертную тарелку
    changeDeviceSet(personList, FIRST_VIP, OpType::SUBTRACT, DeviceType::VIP_PLATE);
    title = std::to_string(FIRST_VIP) + ": they took his vip plate";
    printInfo(personList, title);
}
