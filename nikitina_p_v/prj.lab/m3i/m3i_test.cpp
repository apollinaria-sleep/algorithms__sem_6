#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <m3i/m3i.h>


TEST_CASE("init_simple") {
    int dim0 = rand() % 10 + 1;
    int dim1 = rand() % 10 + 1;
    int dim2 = rand() % 10 + 1;

    M3i vec(dim0, dim1, dim2);
    CHECK(vec.Size(0) == dim0);
    CHECK(vec.Size(1) == dim1);
    CHECK(vec.Size(2) == dim2);
}

TEST_CASE("init_3dims") {
    int dim0 = rand() % 10 + 1;
    int dim1 = rand() % 10 + 1;
    int dim2 = rand() % 10 + 1;
    int val = rand() % 100;

    M3i vec(dim0, dim1, dim2, val);
    CHECK(vec.Size(0) == dim0);
    CHECK(vec.Size(1) == dim1);
    CHECK(vec.Size(2) == dim2);
    for (int i = 0; i < dim0; i++) {
        for (int j = 0; j < dim1; j++) {
            for (int k = 0; k < dim2; k++) {
                CHECK(vec.At(i, j, k) == val);
            }
        }
    }
}

TEST_CASE("init_1dims") {
    int dim = rand() % 10 + 1;
    int val = rand() % 100;

    M3i vec(dim, val);
    CHECK(vec.Size(0) == dim);
    CHECK(vec.Size(1) == dim);
    CHECK(vec.Size(2) == dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            for (int k = 0; k < dim; k++) {
                CHECK(vec.At(i, j, k) == val);
            }
        }
    }
}

TEST_CASE("init_initializer_list") {
    std::initializer_list<
            std::initializer_list<std::initializer_list<int>>> inList = {{{0, 1, 2},
                                                                          {3, 4, 5},
                                                                          {6, 7, 8}}};
    M3i vec(inList);
    CHECK(vec.Size(0) == 1);
    CHECK(vec.Size(1) == 3);
    CHECK(vec.Size(2) == 3);
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                CHECK(vec.At(i, j, k) == i * 3 * 3 + j * 3 + k);
            }
        }
    }
}

TEST_CASE("copying_check") {
    M3i vec({{{0, 1}, {2, 3}}, {{4, 5}, {6, 7}}});

    M3i vec1(vec);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                CHECK(vec1.At(i, j, k) == i * 2 * 2 + j * 2 + k);
            }
        }
    }

    M3i vec2 = vec;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                CHECK(vec2.At(i, j, k) == i * 2 * 2 + j * 2 + k);
            }
        }
    }

    M3i vec3 = M3i(vec);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                CHECK(vec3.At(i, j, k) == i * 2 * 2 + j * 2 + k);
            }
        }
    }
}

TEST_CASE("at_check") {
    M3i vec({{{0, 1}, {2, 3}}, {{4, 5}, {6, 7}}});

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                CHECK(vec.At(i, j, k) == i * 2 * 2 + j * 2 + k);
            }
        }
    }

    vec.At(1, 1, 1) = -1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                if (i != 1 || j != 1 || k != 1) {
                    CHECK(vec.At(i, j, k) == i * 2 * 2 + j * 2 + k);
                } else {
                    CHECK(vec.At(i, j, k) == -1);
                }
            }
        }
    }
}

TEST_CASE("clone_check") {
    M3i vec({{{0, 1}, {2, 3}}, {{4, 5}, {6, 7}}});
    M3i clone_vec = vec.Clone();

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                CHECK(vec.At(i, j, k) == clone_vec.At(i, j, k));
                clone_vec.At(i, j, k) = vec.At(i, j, k) + 1;
                CHECK(clone_vec.At(i, j, k) == i * 2 * 2 + j * 2 + k + 1);
                CHECK(vec.At(i, j, k) == i * 2 * 2 + j * 2 + k);
            }
        }
    }
}

TEST_CASE("fill_check") {
    M3i vec({{{0, 1}, {2, 3}}, {{4, 5}, {6, 7}}});

    int val = rand() % 100;
    vec.Fill(val);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                CHECK(vec.At(i, j, k) == val);
            }
        }
    }
}

TEST_CASE("exceptions_check") {
    // проверка CorrectSize
    int dim0 = rand() % 10 + 1;
    int dim1 = rand() % 10 + 1;
    int dim2 = rand() % 10 + 1;

    bool error = false;
    try {
        M3i vec(dim0 * (-1), dim1, dim2);
    } catch (std::exception& e) {
        error = true;
    }
    CHECK(error);
    error = false;
    try {
        M3i vec(dim0, dim1 * (-1), dim2);
    } catch (std::exception& e) {
        error = true;
    }
    CHECK(error);
    error = false;
    try {
        M3i vec(dim0, dim1, dim2 * (-1));
    } catch (std::exception& e) {
        error = true;
    }
    CHECK(error);

    // проверка CorrectIndex
    M3i vec({{{0, 1}, {2, 3}}, {{4, 5}, {6, 7}}});
    error = false;
    try {
        vec.At(-1, 1, 1);
    } catch (std::exception& e) {
        error = true;
    }
    CHECK(error);
    error = false;
    try {
        vec.At(1, 1, 2);
    } catch (std::exception& e) {
        error = true;
    }
    CHECK(error);
}

TEST_CASE("resize_check") {
    int dim = rand() % 10;
    int val = rand() % 100;
    M3i vec(dim, val);

    bool error = true;
    try {
        vec.At(dim - 1, dim - 1, dim);
    } catch (std::exception& e) {
        error = true;
    }
    CHECK(error);

    vec.Resize(dim + 1, dim + 1, dim + 1);
    CHECK(vec.Size(0) == dim + 1);
    CHECK(vec.Size(1) == dim + 1);
    CHECK(vec.Size(2) == dim + 1);
    vec.At(dim, dim, dim) = -1;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            for (int k = 0; k < dim; k++) {
                CHECK(vec.At(i, j, k) == val);
            }
        }
    }
    CHECK(vec.At(dim, dim, dim) == -1);
}
