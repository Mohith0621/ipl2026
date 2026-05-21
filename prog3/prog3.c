#include <stdio.h>

// Function to print bits of an integer
void printBits(int num)
{
    int bits = sizeof(int) * 8;   // Number of bits in int

    printf("Bits: ");
    for (int i = bits - 1; i >= 0; i--)
    {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

// Function to count number of 1 bits
int countOnes(int num)
{
    int count = 0;

    while (num != 0)
    {
        count += num & 1;   // Check last bit
        num >>= 1;          // Right shift
    }

    return count;
}

int main()
{
    int num;

    printf("Enter an integer: ");
    scanf("%d", &num);

    printBits(num);

    printf("Number of 1 bits = %d\n", countOnes(num));

    return 0;
}