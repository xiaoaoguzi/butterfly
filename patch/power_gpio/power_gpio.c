#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <plat/io.h>
#include <plat/cpu.h>
#include <mach/io.h>
#include <mach/am_regs.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <butterfly/power_gpio.h>
#include <linux/pinctrl/consumer.h>
#include <linux/amlogic/aml_gpio_consumer.h>

int power_set_gpio(int val)
{
	gpio_direction_output(GPIOY_4,val);
	printk(KERN_INFO "***Power gpio %s is %d\n",val==0 ? "off":"on" ,val);
	return 0;
	
}
EXPORT_SYMBOL(power_set_gpio);

static int  power_gpio_probe(struct platform_device *pdev)
{
 int ret;
 
	printk("###power_gpio_probe start###\n");
	
	
	
	ret = gpio_request(GPIOY_4,power_gpio);
	if(ret < 0){
		printk("request gpio:%d failure\n",GPIOY_4);
		ret = -EINVAL;
		goto err;
	}
	
	power_set_gpio(1);
	return 0;
	
err:
	gpio_free(GPIOY_4);
	return 0;
}

static int  power_gpio_remove(struct platform_device *pdev)
{
	gpio_free(GPIOY_4);
	return 0;
}

static const struct of_device_id power_gpio_dt_match[]={
	{	.compatible = "butterfly,power_gpio",
	},
	{},
};

static struct platform_driver power_gpio_driver = {
	.driver = {
		.name = "power_gpio",
		.owner = THIS_MODULE,
		.of_match_table = power_gpio_dt_match,
	},
	.probe = power_gpio_probe,
	.remove = power_gpio_remove,
};

static int __init power_gpio_init(void)
{
	return platform_driver_register(&power_gpio_driver);
}
arch_initcall(power_gpio_init);

static void __exit power_gpio_exit(void)
{
	platform_driver_unregister(&power_gpio_driver);
}
module_exit(power_gpio_exit);
MODULE_DESCRIPTION("chenmuyuan power gpio test driver");
MODULE_LICENSE("GPL v2");
