#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <asm/io.h>
#include <asm/current.h>
#include <asm/pgtable.h>
#include <linux/highmem.h>


// MODULE_LICENSE("Dual BSD/GPL");
void get_process_kernel_space_address(struct task_struct *task){

    pgd_t *pgd;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;

    struct mm_struct *mm;
    unsigned long va = 0xc0000123,pa;
    mm = task->mm;
    if(mm==NULL){
        return 0;
    }
    printk("PID: %d\n", task->pid);
    printk("va = %#lx\n", va);
    pgd = pgd_offset(task->mm,va);
    printk("PGDIR_SHIFT:%#lx,  PTRS_PER_PGD:%#lx, PAGE_MASK:%#lx\n", PGDIR_SHIFT, PTRS_PER_PGD,PAGE_MASK);
    printk("pgd_offset(task->mm,va): %#lx;\ttask->mm->pgd: %#lx,\tpgd_index(va): %#lx\n", pgd,task->mm->pgd, pgd_index(va));
    printk("pgd_val(*pgd):%#lx\n", pgd_val(*pgd));
    pud = pud_offset(pgd,va);
    printk("pud_offset(pgd,va): %#lx;\t(pud_t *)pgd_page_vaddr(*pgd): %#lx\n", pud, (pud_t *)pgd_page_vaddr(*pgd) );
    printk("pud_val(*pud):%#lx\n", pud_val(*pud));
    pmd = pmd_offset(pud,va);
    printk("pmd_offset(pud,va): %#lx;\t(pmd_t *)pud_page_vaddr(*pud): %#lx,\tpmd_index(va): %#lx\n", pmd, (pmd_t *)pud_page_vaddr(*pud) ,pmd_index(va));
    printk("pmd_val(*pmd):%#lx\n", pmd_val(*pmd));
    pte = pte_offset_map(pmd,va);
    printk("PAGE_MASK: %#lx\n", PAGE_MASK);
    printk("pte_offset(pmd,va): %#lx,\t(pte_t *)(pmd_page_vaddr(*pmd)): %#lx\n", pte, (pte_t *)(pmd_page_vaddr(*pmd)));
    pa = (pte_val(*pte)&PAGE_MASK)|(va&~PAGE_MASK);
    printk("pte_val(*pte): %#lx,\tPAGE_MASK: %#lx\n", pte_val(*pte), PAGE_MASK);
    printk("task: %s va_to_pa: [%#lx]\n========\n",task->comm,pa);
}

static int hello_init(void)
{
	int counter = 0; 
        struct task_struct *task;
        for_each_process(task)
        {
                if(task == NULL){
                        continue;
                }
                else{
                        get_process_kernel_space_address(task);
                }
        }
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_INFO "Goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);
