#include <iostream>
#include <vector>
#include <algorithm>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    int rows;
    int cols;

public:
    // Конструктор
    Matrix(int num_rows, int num_cols) : rows(num_rows), cols(num_cols) {
        data.resize(rows, std::vector<int>(cols, 0));
    }
    
    // Конструктор с инициализацией данными
    Matrix(std::vector<std::vector<int>> input_data) {
        data = input_data;
        rows = data.size();
        if (rows > 0) {
            cols = data[0].size();
        } else {
            cols = 0;
        }
    }
    
    // Получение количества строк
    int getRows() const { return rows; }
    
    // Получение количества столбцов
    int getCols() const { return cols; }
    
    // Получение элемента
    int get(int row, int col) const {
        return data[row][col];
    }
    
    // Установка элемента
    void set(int row, int col, int value) {
        data[row][col] = std::max(0, std::min(255, value)); // Ограничение 0-255
    }
    
    // Вывод матрицы
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    // Получение всех данных
    std::vector<std::vector<int>> getData() const {
        return data;
    }
};

// 1. Функция инверсии изображения
void invert_image(Matrix* img) {
    for (int i = 0; i < img->getRows(); i++) {
        for (int j = 0; j < img->getCols(); j++) {
            int old_value = img->get(i, j);
            int new_value = 255 - old_value;
            img->set(i, j, new_value);
        }
    }
}

// 2. Функция увеличения яркости
void brighten_image(Matrix* img, int value) {
    for (int i = 0; i < img->getRows(); i++) {
        for (int j = 0; j < img->getCols(); j++) {
            int old_value = img->get(i, j);
            int new_value = old_value + value;
            img->set(i, j, new_value);
        }
    }
}

// 3. Функция изменения контрастности
void apply_contrast(Matrix* img, float factor) {
    for (int i = 0; i < img->getRows(); i++) {
        for (int j = 0; j < img->getCols(); j++) {
            int old_value = img->get(i, j);
            // Преобразование для контрастности
            float normalized = old_value / 255.0f;
            float contrasted = normalized * factor;
            int new_value = static_cast<int>(contrasted * 255);
            img->set(i, j, new_value);
        }
    }
}

// Функция для создания тестового изображения 3x3
Matrix create_test_image() {
    std::vector<std::vector<int>> test_data = {
        {100, 150, 200},
        {50, 180, 90},
        {220, 30, 120}
    };
    return Matrix(test_data);
}

// Функция для проверки результатов
void test_filters() {
    std::cout << "=== ТЕСТИРОВАНИЕ ФИЛЬТРОВ ===" << std::endl;
    
    // Создаем тестовое изображение
    Matrix img = create_test_image();
    
    std::cout << "Исходное изображение:" << std::endl;
    img.print();
    std::cout << std::endl;
    
    // Тестируем инверсию
    Matrix img_invert = create_test_image();
    invert_image(&img_invert);
    std::cout << "После инверсии:" << std::endl;
    img_invert.print();
    std::cout << std::endl;
    
    // Тестируем осветление
    Matrix img_bright = create_test_image();
    brighten_image(&img_bright, 50);
    std::cout << "После осветления на 50:" << std::endl;
    img_bright.print();
    std::cout << std::endl;
    
    // Тестируем контрастность
    Matrix img_contrast = create_test_image();
    apply_contrast(&img_contrast, 1.5f);
    std::cout << "После увеличения контрастности (factor=1.5):" << std::endl;
    img_contrast.print();
    std::cout << std::endl;
    
    // Проверяем пример из задания
    std::cout << "=== ПРОВЕРКА ПРИМЕРА ИЗ ЗАДАНИЯ ===" << std::endl;
    std::vector<std::vector<int>> example_data = {{100, 150, 200}};
    Matrix example_img(example_data);
    
    std::cout << "Исходное: ";
    for (int j = 0; j < example_img.getCols(); j++) {
        std::cout << example_img.get(0, j) << " ";
    }
    std::cout << std::endl;
    
    invert_image(&example_img);
    std::cout << "Инверсия: ";
    for (int j = 0; j < example_img.getCols(); j++) {
        std::cout << example_img.get(0, j) << " ";
    }
    std::cout << std::endl;
    
    // Проверяем граничные значения
    std::cout << std::endl << "=== ТЕСТ ГРАНИЧНЫХ ЗНАЧЕНИЙ ===" << std::endl;
    std::vector<std::vector<int>> edge_data = {{0, 255, 300, -10}};
    Matrix edge_img(edge_data);
    
    std::cout << "До обработки: ";
    edge_img.print();
    
    brighten_image(&edge_img, 100);
    std::cout << "После осветления на 100: ";
    edge_img.print();
}

int main() {
    test_filters();
    return 0;
}
