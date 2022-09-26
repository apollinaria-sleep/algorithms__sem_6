 #include <m3i/m3i.h>
 #include <iostream>

// конструктор M3iInfo
M3i::M3iInfo::M3iInfo(int dim0, int dim1, int dim2) {
    shape[0] = dim0;
    shape[1] = dim1;
    shape[2] = dim2;
    maxSize = dim0 * dim1 * dim2;
    data = new int[maxSize]();
}

// конструкторы
M3i::M3i(int dim0, int dim1, int dim2) { // незаполняющий
    CorrectSize(dim0, dim1, dim2);
    info = new M3iInfo(dim0, dim1, dim2);
}

M3i::M3i(int dim0, int dim1, int dim2, int val) { // заполняющий с разными размерами
    CorrectSize(dim0, dim1, dim2);
    info = new M3iInfo(dim0, dim1, dim2);
    for (int i = 0; i < info->maxSize; i++) {
        info->data[i] = val;
    }
}

M3i::M3i(int dim, int val) { // заполняющий с одним размером
    *this = M3i(dim, dim, dim, val);
}

M3i::M3i(std::initializer_list<
        std::initializer_list<std::initializer_list<int>>> inList) { // инициализация с помощью списка
    int dim0 = inList.size();
    int dim1 = inList.begin()->size();
    int dim2 = inList.begin()->begin()->size();
    
    info = new M3iInfo(dim0, dim1, dim2);
    int iter = 0;
    for (auto &list : inList) {
        for (auto &sublist : list) {
            for (auto &value : sublist) {
                info->data[iter++] = value;
            }
        }
    }
}

// копирование
M3i::M3i(const M3i &other) {
    info = other.info;
    atomic_fetch_add(&info->counter, 1);
}

M3i &M3i::operator=(const M3i &other) {
    free();
    info = other.info;
    atomic_fetch_add(&info->counter, 1);
    return *this;
}

// move-конструктор
M3i &M3i::operator=(M3i &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    free();
    info = other.info;
    other.info = nullptr;
    return *this;
}

// деструктор
M3i::~M3i() {
    free();
}

// полная копия данных
M3i M3i::Clone() const {
    std::lock_guard<std::mutex>(info->mutex);
    M3i cloned(info->shape[0], info->shape[1], info->shape[2]);
    for (int i = 0; i < info->maxSize; i++) {
        cloned.info->data[i] = info->data[i];
    }
    return cloned;
}

// заполнение одним значением
void M3i::Fill(int val) {
    std::lock_guard<std::mutex>(info->mutex);
    for (int i = 0; i < info->maxSize; i++) {
        info->data[i] = val;
    }
}

// изменение размера
M3i &M3i::Resize(int dim0, int dim1, int dim2) {
    CorrectSize(dim0, dim1, dim2);

    std::lock_guard<std::mutex>(info->mutex);

    int* t_buffer = new int[dim0 * dim1 * dim2];
    for (int i = 0; i < (info->shape[0] < dim0 ? info->shape[0] : dim0); i++) {
        for (int j = 0; j < (info->shape[1] < dim1 ? info->shape[1] : dim1); j++) {
            for (int k = 0; k < (info->shape[2] < dim2 ? info->shape[2] : dim2); k++) {
                t_buffer[i * dim1 * dim2 + j * dim2 + k] = this->At(i, j, k);
            }
        }
    }

    delete[] info->data;
    info->shape[0] = dim0;
    info->shape[1] = dim1;
    info->shape[2] = dim2;
    info->maxSize = dim0 * dim1 * dim2;
    info->data = t_buffer;

    return *this;
}

// получение размера по одному из измерений
int M3i::Size(int dim) const {
    if (dim < 0 || dim > 2) {
        throw Exceptions("M3i has dimension 3 (dimension must be between 0 and 2)\n");
    }
    return info->shape[dim];
}

// доступ к элементу по индексу
int &M3i::At(int i, int j, int k) {
    CorrectIndex(i,j,k);
    return info->data[i * info->shape[1] * info->shape[2] + j * info->shape[2] + k];
}

int M3i::At(int i, int j, int k) const {
    CorrectIndex(i,j,k);
    int val = info->data[i * info->shape[1] * info->shape[2] + j * info->shape[2] + k];
    return val;
}

std::istream &M3i::ReadFrom(std::istream &in) {
    if (info != nullptr) {
        std::lock_guard<std::mutex>(info->mutex);
        free();
    }

    std::string str_size;
    in >> str_size;
    if (str_size != "size:") {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    int dim0, dim1, dim2;
    in >> dim0 >> dim1 >> dim2;
    if (dim0 <= 0 || dim1 <= 0 || dim2 <= 0) {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    M3i new_m3i = M3i(dim0, dim1, dim2);
    for (int i = 0; i < dim0; i++) {
        for (int j = 0; j < dim1; j++) {
            for (int k = 0; k < dim2; k++) {
                in >> new_m3i.info->data[i * dim1 * dim2 + j * dim2 + k];
            }
        }
    }

    *this = new_m3i;
    return in;
}

std::ostream &M3i::WriteTo(std::ostream &out) const {
    std::lock_guard<std::mutex>(info->mutex);

    out << "size:" << info->shape[0] << ' ' << info->shape[1] << ' ' << info->shape[2] << '\n';
    for (int i = 0; i < info->shape[0]; i++) {
        for (int j = 0; j < info->shape[1]; j++) {
            for (int k = 0; k < info->shape[2]; k++) {
                out << At(i, j, k) << ' ';
            }
            out << '\n';
        } 
        out << '\n';
    }
    return out;
}

std::istream &operator>>(std::istream &in, M3i &vec) {
    return vec.ReadFrom(in);
}

std::ostream &operator<<(std::ostream &out, const M3i &vec) {
    return vec.WriteTo(out);
}

void M3i::free() {
    if (info == nullptr) {
        return;
    }

    std::lock_guard<std::mutex>(info->mutex);
    if (info->counter - 1 == 0) {
        delete[] info->data;
        delete info;
    }
    info = nullptr;
}

void M3i::CorrectSize(int dim0, int dim1, int dim2) const {
    if (dim0 <= 0) {
        throw Exceptions("Первое измерение не положительно\n");
    }
    if (dim1 <= 0) {
        throw Exceptions("Второе измерение не положительно\n");
    }
    if (dim2 <= 0) {
        throw Exceptions("Третье измерение не положительно\n");
    }
}

void M3i::CorrectIndex(int i, int j, int k) const {
    if (i < 0 || i >= info->shape[0]) {
        throw Exceptions("Первый индекс не верный\n");
    }
    if (j < 0 || j >= info->shape[1]) {
        throw Exceptions("Второй индекс не верный\n");
    }
    if (k < 0 || k >= info->shape[2]) {
        throw Exceptions("Третий индекс не верный\n");
    }
}
// добавить конструктор в M3iInfo