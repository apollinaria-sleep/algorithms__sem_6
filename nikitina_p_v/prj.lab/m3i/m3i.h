#pragma once
#ifndef M3I_M3I_HEAD_H_2022_09_24
#define M3I_M3I_HEAD_H_2022_09_24

#include <atomic>
#include <initializer_list>
#include <iosfwd>
#include <memory>
#include <mutex>
#include <exception>
#include <string>
#include <string_view>


class M3i {
public:
  // конструкторы
  M3i() = default;                            // дефолтный
  M3i(int dim0, int dim1, int dim2);          // незаполняющий -- checked
  M3i(int dim0, int dim1, int dim2, int val); // заполняющий с разными размерами -- checked
  M3i(int dim, int val);                      // заполняющий с одним размером -- checked
  M3i(std::initializer_list<
      std::initializer_list<std::initializer_list<int>>>); // инициализация с помощью списка -- checked

  // копирование
  M3i(const M3i &other);            // нужен подсчет ссылок --checked
  M3i &operator=(const M3i &other); // нужен подсчет ссылок --checked

  // move-конструктор
  M3i &operator=(M3i &&other) noexcept; // -- checked

  // деструктор
  ~M3i();

  // полная копия данных
  M3i Clone() const; // -- checked

  // заполнение одним значением
  void Fill(int val); // -- checked

  // изменение размера
  M3i &Resize(int dim0, int dim1, int dim2); // -- checked

  // получение размера по одному из измерений
  int Size(int dim) const; // -- checked

  // доступ к элементу по индексу
  int &At(int i, int j, int k); // -- checked
  int At(int i, int j, int k) const; // -- checked

  std::ostream &WriteTo(std::ostream &) const;
  std::istream &ReadFrom(std::istream &);

private:
  // вспомогательная структура с характеристиками m3i
  class M3iInfo {
  public:
    // конструктор
    M3iInfo(int dim0, int dim1, int dim2);

    int shape[3] = {0};              // размеры m3i
    int maxSize = 0;                 // максимальная вместимость m3i
    int *data = nullptr;             // указатель на массив данных
    std::mutex mutex;                // для многопоточного использования класса
    std::atomic_int16_t counter = 1; // потокобезопасный счетчик ссылок
  } *info = nullptr;

  // класс ошибок
  class Exceptions : public std::exception {
  public:
    explicit Exceptions(std::string_view error) : m_error{error} {}
    const char* what() const noexcept override {
      return m_error.c_str();//;
    }
  private:
    std::string m_error;
  };

  void free();
  void CorrectSize(int dim0, int dim1, int dim2) const; // -- checked
  void CorrectIndex(int i, int j, int k) const; // -- checked
};

std::istream &operator>>(std::istream &, M3i &);

std::ostream &operator<<(std::ostream &, const M3i &);

#endif