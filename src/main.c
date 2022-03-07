#include <zephyr.h>
#include <sys/printk.h>

#include <bluetooth/bluetooth.h>
#include <usb/usb_device.h>

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

static void adv_recv(const bt_addr_le_t *addr, int8_t rssi, uint8_t type,
                     struct net_buf_simple *ad)
{
    // A4:C1:38
    if (addr->a.val[5] != 0xA4 || addr->a.val[4] != 0xC1 || addr->a.val[3] != 0x38 || type != 0)
    {
        return;
    }

    printk("ENV1,%02X:%02X:%02X:%02X:%02X:%02X,%d,",
           addr->a.val[5], addr->a.val[4], addr->a.val[3],
           addr->a.val[2], addr->a.val[1], addr->a.val[0], rssi);

    for (int i = 0; i < ad->len; i++)
    {
        printk("%02X", ad->data[i]);
    }
    printk("\n");
}

void main(void)
{
    const struct bt_le_scan_param scan_param = {
        .type = BT_LE_SCAN_TYPE_PASSIVE,
        .options = BT_LE_SCAN_OPT_NONE,
        .interval = BT_GAP_SCAN_FAST_INTERVAL,
        .window = BT_GAP_SCAN_FAST_WINDOW,
    };

    if (usb_enable(NULL))
    {
        return;
    }

    if (bt_enable(NULL))
    {
        return;
    }

    if (bt_le_scan_start(&scan_param, adv_recv))
    {
        return;
    }

    while (1)
    {
        k_sleep(K_SECONDS(1));
    }
}
