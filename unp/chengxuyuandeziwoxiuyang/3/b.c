int shared = 1;
void swap(int *px, int *py)
{
    *px ^= *py ^= *px ^= *py;
}
