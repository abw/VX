#include <vx.h>


void test_vx();


int main(
    int argc, char **argv, char **env
) {
    test_vx();
    return 0;
}


void test_vx() {
    VX vx = VX_new();
    printf("1..2\n");
    printf("ok 1 - created new VX object\n");
    VX_free(vx);
    printf("ok 2 - cleaned VX object\n");
}

