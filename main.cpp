#include <iostream>
#include <cassert>
#include <vector>
#include <string>

// первая вип-персона
const int FIRST_VIP = 0;
// вторая вип-персона
const int SECOND_VIP = 1;
// количество персон
const int PERSON_COUNT = 12;
// общее количество приборов
const int DEVICE_COUNT = 7;
// две стороны стола
enum class RowType { FIRST, SECOND };
// операции добавления/удаления персоне приборов
enum class OpType { ADD, SUBTRACT };
// приборы
enum class DeviceType { FORK, SPOON, KNIFE, PLATE, CHAIR, VIP_SPOON, VIP_PLATE };

// меняет массив, заполняя его необходимыми данными
void initPersonList(int (&arr)[PERSON_COUNT][DEVICE_COUNT]) {
    for (int i = 0; i < PERSON_COUNT; ++i) {
        arr[i][static_cast<int>(DeviceType::FORK)] = 1;
        arr[i][static_cast<int>(DeviceType::SPOON)] = 1;
        arr[i][static_cast<int>(DeviceType::KNIFE)] = 1;
        arr[i][static_cast<int>(DeviceType::PLATE)] = 1;
        arr[i][static_cast<int>(DeviceType::CHAIR)] = 1;

        if (i == FIRST_VIP || i == SECOND_VIP) {
            arr[i][static_cast<int>(DeviceType::VIP_SPOON)] = 1;
            arr[i][static_cast<int>(DeviceType::VIP_PLATE)] = 1;
        }
    }
}

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

// рассчитывает место в одномерном массиве для введенных "ряд" - "место"
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
            // Но можно вызвать предупреждение:
            // assert(result >= 0);
            break;
    }
}

int main() {
    int seatNumber = 0;
    std::string title;

    int personList[PERSON_COUNT][DEVICE_COUNT] = { 0 };

    // гости только пришли
    initPersonList(personList);
    printInfo(personList, "starting position of guests");

    // Первый ряд, пятое место. Добавили стул
    seatNumber = getSeatNumber(RowType::FIRST, 5);
    changeDeviceSet(personList, seatNumber, OpType::ADD, DeviceType::CHAIR);
    title = std::to_string(seatNumber) + ": received chair";
    printInfo(personList, title);

    // Второй ряд, третье место. Украдена ложка
    seatNumber = getSeatNumber(RowType::SECOND, 3);
    changeDeviceSet(personList, seatNumber, OpType::SUBTRACT, DeviceType::SPOON);
    title = std::to_string(seatNumber) + ": his spoon was stolen";
    printInfo(personList, title);

    // Первая вип-персона. Поделилась ложкой
    changeDeviceSet(personList, FIRST_VIP, OpType::SUBTRACT, DeviceType::SPOON);
    title = std::to_string(FIRST_VIP) + ": he shared a spoon";
    printInfo(personList, title);

    // Второй ряд, третье место. Ложка добавлена
    changeDeviceSet(personList, seatNumber, OpType::ADD, DeviceType::SPOON);
    title = std::to_string(seatNumber) + ": received spoon";
    printInfo(personList, title);

    // Первая вип-персона. Забрали десертную тарелку
    changeDeviceSet(personList, FIRST_VIP, OpType::SUBTRACT, DeviceType::VIP_PLATE);
    title = std::to_string(FIRST_VIP) + ": they took his vip plate";
    printInfo(personList, title);
}
