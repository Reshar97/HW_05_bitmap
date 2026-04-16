#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/bitmap.h>
#include <linux/slab.h>

#define NUM_BLOCKS 64  // Количество блоков памяти (бит)

static unsigned long *block_map;

static int __init ex_bitmap_init(void)
{
    int i, block1, block2, block3;

    printk(KERN_INFO "ex_bitmap: Модуль загружен\n");

    // Выделяем память для битовой карты
    block_map = kzalloc(BITS_TO_LONGS(NUM_BLOCKS) * sizeof(long), GFP_KERNEL);
    if (!block_map)
        return -ENOMEM;

    // Инициализация: все блоки свободны (биты = 0)
    bitmap_zero(block_map, NUM_BLOCKS);
    printk(KERN_INFO "ex_bitmap: Все блоки памяти свободны\n");

    // Имитация выделения блоков 5, 10, 15
    block1 = 5;
    block2 = 10;
    block3 = 15;

    set_bit(block1, block_map);
    set_bit(block2, block_map);
    set_bit(block3, block_map);

    printk(KERN_INFO "ex_bitmap: Выделены блоки: %d, %d, %d\n", block1, block2, block3);

    // Поиск первого свободного блока
    i = find_first_zero_bit(block_map, NUM_BLOCKS);
    printk(KERN_INFO "ex_bitmap: Первый свободный блок: %d\n", i);

    // Освобождение блока 10
    clear_bit(block2, block_map);
    printk(KERN_INFO "ex_bitmap: Блок %d освобождён\n", block2);

    return 0;
}

static void __exit ex_bitmap_exit(void)
{
    kfree(block_map);
    printk(KERN_INFO "ex_bitmap: Модуль Выгружен\n");
}

module_init(ex_bitmap_init);
module_exit(ex_bitmap_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anton Zubin");
MODULE_DESCRIPTION("Example Bitmap");
