#include <zephyr/kernel.h>

int main(void)
{
    int64_t previous_time = k_uptime_get();
    LOG_INF(" *hello_world* Program application is Running");

    while (1) {
        int64_t current_time = k_uptime_get();
        int64_t diff = current_time - previous_time;

        printk("Hello World | Time: %lld.%03lld s | Diff: %lld ms\n",
               current_time / 1000,
               current_time % 1000,
               diff);

        previous_time = current_time;

        k_sleep(K_SECONDS(1));
    }

    return 0;
}