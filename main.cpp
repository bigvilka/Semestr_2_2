#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

class tree
{
    public:
    bool type;
    int* ival;
    struct complex_val
    {
        int re;
        int im;
    }*cval;
    struct node
    {
        void* data;
        struct node *lo, *eq, *hi;
    }*defnode;
    struct node* create_node(tree* tr, void* numptr)
    {
        struct node* buffer = new struct node;
        if(tr->type)
        {
            buffer->data = operator new(sizeof(complex_val));
            complex_val* read = (complex_val*)numptr;
            tr->cval = (complex_val*)buffer->data;
            tr->cval->re = read->re;
            tr->cval->im = read->im;
            buffer->lo = buffer->eq = buffer->hi = NULL;
            return buffer;
        }
        else
        {
            buffer->data = operator new(sizeof(int));
            int* readi = (int*)numptr;
            tr->ival = (int*)buffer->data;
            *(tr->ival) = *readi;
            buffer->lo = buffer->eq = buffer->hi = NULL;
            return buffer;
        }
    }

    void init()
    {
        defnode = NULL;
    }

    void insert(tree* tr, struct node** root, void* numptr)
    {
        if(!(*root))
        {
            *root = create_node(tr, numptr);
            return;
        }
        if(tr->type)
        {
            tr->cval = (complex_val*)(*root)->data;
            complex_val* read = (complex_val*)numptr;
            if(read->re < tr->cval->re)
                insert(tr, &((*root)->lo ), numptr);
            else if (read->re > tr->cval->re)
                insert(tr, &((*root)->hi ), numptr);
            else if (read->im < tr->cval->im)
                insert(tr, &((*root)->lo ), numptr);
            else if (read->im > tr->cval->im)
                insert(tr, &((*root)->hi ), numptr);
            else
                insert(tr, &((*root)->eq ), numptr);
        }
        else
        {
            tr->ival = (int*)(*root)->data;
            int* readi = (int*)numptr;
            if(*readi < *(tr->ival))
                insert(tr, &((*root)->lo ), numptr);
            else if (*readi > *(tr->ival))
                insert(tr, &((*root)->hi ), numptr);
            else
                insert(tr, &((*root)->eq ), numptr);
        }
    }

    int search(tree* tr, struct node *root, void *numptr)
    {
        if (!root)
        {
            if(tr->type)
            {
                tr->cval = (complex_val*)numptr;
                printf("Не найдено%d+%di.\n", tr->cval->re, tr->cval->im);
                return 0;
            }
            else
            {
                tr->ival = (int*)numptr;
                printf("Не найдено %d.\n", *(tr->ival));
                return 0;
            }
        }
        if(tr->type)
        {
            tr->cval = (complex_val*)root->data;
            complex_val* read = (complex_val*)numptr;
            if (read->re < cval->re)
                return search(tr, root->lo, numptr);
            else if (read->re > cval->re)
                return search(tr, root->hi, numptr);
            else if (read->im < cval->im)
                return search(tr, root->lo, numptr);
            else if (read->im > cval->im)
                return search(tr, root->hi, numptr);
            else
            {
                printf("Найдено %d+%di.\n", read->re, read->im);
                return 0;
            }
        }
        else
        {
            tr->ival = (int*)root->data;
            int* readi = (int*)numptr;
            if (*readi < *(tr->ival))
                return search(tr, root->lo, numptr);
            else if (*readi > *(tr->ival))
                return search(tr, root->hi, numptr);
            else
            {
                printf("Найдено %d.\n", *readi);
                return 0;
            }
        }
    }

    void traverse(tree* tr, struct node* root, int index)
    {
        if (root)
        {
            if(tr->type)
            {
                tr->cval = (complex_val*)root->data;
                if(index == 0)
                    printf("");
                if(index == 1)
                    printf("[");
                if(index == 2)
                    printf("(");
                printf("%d+%di", tr->cval->re, tr->cval->im);
                if(index == 0)
                    printf("");
                if(index == 1)
                    printf("] ");
                if(index == 2)
                    printf(") ");
                traverse(tr, root->eq, 1);
                traverse(tr, root->lo, 2);
                traverse(tr, root->hi, 2);
            }
            else
            {
                tr->ival = (int*)root->data;
                if(index == 0)
                    printf("");
                if(index == 1)
                    printf("[");
                if(index == 2)
                    printf("(");
                printf("%d", *(tr->ival));
                if(index == 0)
                    printf("");
                if(index == 1)
                    printf("] ");
                if(index == 2)
                    printf(")");
                traverse(tr, root->eq, 1);
                traverse(tr, root->lo, 2);
                traverse(tr, root->hi, 2);
            }
        }
    }
    struct node* nodepasser(tree* tr, struct node* root, void* num)
    {
            struct node* mod = NULL;
            nodepasser_iterative(tr, root, num, &mod);
            return mod;
    }

    void nodepasser_iterative(tree* tr, struct node* root, void* num, struct node** mod)
    {
        if(root)
        {
            if(tr->type)
            {
                tr->cval = (complex_val*)root->data;
                complex_val* read = (complex_val*)num;
                if((tr->cval->re == read->re) && (tr->cval->im == read->im))
                {
                    *mod = root;
                }
                else
                {
                    if(root->lo)
                    {
                        nodepasser_iterative(tr, root->lo, num, mod);
                    }
                    if(root->eq)
                    {
                        nodepasser_iterative(tr, root->eq, num, mod);
                    }
                    if(root->hi)
                    {
                        nodepasser_iterative(tr, root->hi, num, mod);
                    }
                }
            }
            else
            {
                tr->ival = (int*)root->data;
                int* readi = (int*)num;
                if(*(tr->ival) == *readi)
                {
                    *mod = root;
                }
                else
                {
                    if(root->lo)
                    {
                        nodepasser_iterative(tr, root->lo, num, mod);
                    }
                    if(root->eq)
                    {
                        nodepasser_iterative(tr, root->eq, num, mod);
                    }
                    if(root->hi)
                    {
                        nodepasser_iterative(tr, root->hi, num, mod);
                    }
                }
            }
            return;
        }
    }

    void absorb(tree* tr, struct node* root)
    {
        if(root)
        {
            insert(tr, &defnode, root->data);
            absorb(tr, root->lo);
            absorb(tr, root->eq);
            absorb(tr, root->hi);
        }
    }

    void check_subtree_iterative(tree* tr, struct node* root, struct node* buffer, bool* checker)
    {
        if(root)
        {
            if(buffer)
            {
                if(tr->type)
                {
                    tr->cval = (complex_val*)buffer->data;
                    complex_val* read = (complex_val*)root->data;
                    if((tr->cval->re == read->re) && (tr->cval->im == read->im))
                    {
                        check_subtree_iterative(tr, root->lo, buffer->lo, checker);
                        check_subtree_iterative(tr, root->eq, buffer->eq, checker);
                        check_subtree_iterative(tr, root->hi, buffer->hi, checker);
                    }
                    else
                    {
                        *checker = false;
                    }
                }
                else
                {
                    tr->ival = (int*)buffer->data;
                    int* readi = (int*)root->data;
                    if(*(tr->ival) = *readi)
                    {
                        check_subtree_iterative(tr, root->lo, buffer->lo, checker);
                        check_subtree_iterative(tr, root->eq, buffer->eq, checker);
                        check_subtree_iterative(tr, root->hi, buffer->hi, checker);
                    }
                    else
                    {
                        *checker = false;
                    }
                }
            }
            else
            {
                *checker = false;
            }
        }
        if(!root)
        {
            if(buffer)
            {
                *checker = false;
            }
        }
    }

    bool check_subtree(tree* tr)
    {
        struct node* root = tr->nodepasser(tr, tr->defnode, defnode->data);
        if(!root)
        {
            return false;
        }
        else
        {
            bool checker = true;
            check_subtree_iterative(tr, root, defnode, &checker);
            return checker;
        }
    }

    void free_tree(struct node* root)
    {
        if(root)
        {
            free_tree(root->lo);
            free_tree(root->eq);
            free_tree(root->hi);
            operator delete(root);
        }
    }

    void get_type()
    {
        printf("Выберите тип чисел в дереве\n");
        printf("0. Целые\n");
        printf("1. Комлексные\n");
        scanf("%d", &type);
    }

    void fill_tree(tree* tr)
    {
        if(!tr->type)
        {
            int num, size;
            printf("Введите количество вершин\n");
            scanf("%d", &size);
            printf("Значения:\n");
            for(int i = 0; i < size; i++)
            {
                scanf("%d", &num);
                tr->insert(tr, &tr->defnode, &num);
            }
        }
        else
        {
            int size;
            complex_val cnum;
            printf("Введите количество вершин\n");
            scanf("%d", &size);
            for(int i = 0; i < size; i++)
            {
                scanf("%d %d", &cnum.re, &cnum.im);
                tr->insert(tr, &tr->defnode, &cnum);
            }
        }
    }
};

void subone(tree* tr, tree::node* root)
{
    if (root)
    {
        if(tr->type)
        {
            tr->cval = (tree::complex_val*)root->data;
            tr->cval->re -= 1;
            tr->cval->im -= 1;
            subone(tr, root->lo);
            subone(tr, root->eq);
            subone(tr, root->hi);
        }
        else
        {
            tr->ival = (int*)root->data;
            *(tr->ival) -= 1;
            subone(tr, root->lo);
            subone(tr, root->eq);
            subone(tr, root->hi);
        }
    }
}

void addone(tree* tr, tree::node* root)
{
    if (root)
    {
        if(tr->type)
        {
            tr->cval = (tree::complex_val*)root->data;
            tr->cval->re += 1;
            tr->cval->im += 1;
            addone(tr, root->lo);
            addone(tr, root->eq);
            addone(tr, root->hi);
        }
        else
        {
            tr->ival = (int*)root->data;
            *(tr->ival) += 1;
            addone(tr, root->lo);
            addone(tr, root->eq);
            addone(tr, root->hi);
        }
    }
}

void map(tree** arr_trees, int args, void (*foo)(tree*, tree::node*))
{
    for(int i = 0; i < args; i++)
    {
        foo(arr_trees[i], arr_trees[i]->defnode);
    }
}

void wher(tree* tr2, tree::node* root, int num, bool mode)
{
    if(root)
    {
        if(mode)
        {
            if(tr2->type)
            {
                tr2->cval = (tree::complex_val*)root->data;
                if(tr2->cval->re > num)
                {
                    tr2->insert(tr2, &tr2->defnode, root->data);
                }
                wher(tr2, root->lo, num, mode);
                wher(tr2, root->eq, num, mode);
                wher(tr2, root->hi, num, mode);
            }
            else
            {
                tr2->ival = (int*)root->data;
                if(*(tr2->ival) > num)
                {
                    tr2->insert(tr2, &tr2->defnode, root->data);
                }
                wher(tr2, root->lo, num, mode);
                wher(tr2, root->eq, num, mode);
                wher(tr2, root->hi, num, mode);
            }
        }
        else
        {
            if(tr2->type)
            {
                tr2->cval = (tree::complex_val*)root->data;
                if(tr2->cval->re < num)
                {
                    tr2->insert(tr2, &tr2->defnode, root->data);
                }
                wher(tr2, root->lo, num, mode);
                wher(tr2, root->eq, num, mode);
                wher(tr2, root->hi, num, mode);
            }
            else
            {
                tr2->ival = (int*)root->data;
                if(*(tr2->ival) < num)
                {
                    tr2->insert(tr2, &tr2->defnode, root->data);
                }
                wher(tr2, root->lo, num, mode);
                wher(tr2, root->eq, num, mode);
                wher(tr2, root->hi, num, mode);
            }
        }
    }
}

void program_exit()
{
    printf("Для выхода из программы нажмите \"пробел\", чтобы продолжить нажмите любую другую клавишу.\n" );
    char button = getch();
    if (button == 32)
    {
        exit(0);
    }
}

void test()
{
    printf("Выберите необходимую операцию\n");
    printf("1. Слияние деревьев\n");
    printf("2. Извлечь поддерево\n");
    printf("3. Проверить поддерево\n");
    printf("4. Map деревьев\n");
    printf("5. Построить дерево where\n");
    int mode;
    scanf("%d", &mode);
    if(mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5)
        program_exit();
    if(mode == 1)
    {

    }
    if(mode == 2)
    {

    }
    if(mode == 3)
    {

    }
    if(mode == 4)
    {

    }
    if(mode == 5)
    {

    }
}

void user()
{
    printf("Выберите необходимую операцию\n");
    printf("1. Слияние деревьев\n");
    printf("2. Извлечь поддерево\n");
    printf("3. Поиск узла\n");
    printf("4. Проверить поддерево\n");
    printf("5. Map деревьев\n");
    printf("6. Построить дерево where\n");
    int mode;
    scanf("%d", &mode);
    if(mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5 && mode != 6)
        program_exit();
    if(mode == 1)
    {
        tree tr1, tr2;
        tr1.init();
        tr2.init();
        tr1.get_type();
        printf("Дерево 1 будет содержать дерево 2\n");
        tr1.fill_tree(&tr1);
        printf("Представление дерева 1:\n");
        tr1.traverse(&tr1, tr1.defnode, 0);
        tr2.type = tr1.type;
        printf("\nДерево 2 будет добавлено к дереву 1\n");
        tr2.fill_tree(&tr2);
        printf("Представление дерева 2:\n");
        tr2.traverse(&tr2, tr2.defnode, 0);
        printf("\nСлияние дерева 2 в дерево 1...\n");
        tr1.absorb(&tr2, tr2.defnode);
        printf("\nВыполнено. Результат:\n");
        tr1.traverse(&tr1, tr1.defnode, 0);
        tr1.free_tree(tr1.defnode);
        tr2.free_tree(tr2.defnode);
    }
    if(mode == 2)
    {
        tree tr1, tr2;
        tr1.init();
        tr2.init();
        tr1.get_type();
        tr1.fill_tree(&tr1);
        printf("Представление дерева:\n");
        tr1.traverse(&tr1, tr1.defnode, 0);
        tr2.type = tr1.type;
        printf("\nВведите корень поддерева для извлечения\n");
        if(tr1.type)
        {
            tree::complex_val cnum;
            scanf("%d %d", &cnum.re, &cnum.im);
            tr2.absorb(&tr1, tr1.nodepasser(&tr1, tr1.defnode, &cnum));
        }
        else
        {
            int num;
            printf("\nЗначение:\n");
            scanf("%d", &num);
            printf("Извлечение поддерева... ");
            tr2.absorb(&tr1, tr1.nodepasser(&tr1, tr1.defnode, &num));
        }
        printf("\nРезультат\n");
        if(tr2.defnode)
            tr2.traverse(&tr2, tr2.defnode, 0);
        else
            printf("Вершина не найдена\n");
        tr1.free_tree(tr1.defnode);
        tr2.free_tree(tr2.defnode);
    }
    if(mode == 3)
    {
        tree tr1;
        tr1.init();
        tr1.get_type();
        tr1.fill_tree(&tr1);
        printf("Представление дерева\n");
        tr1.traverse(&tr1, tr1.defnode, 0);
        printf("\nВведите вершину для поиска\n");
        if(tr1.type)
        {
            tree::complex_val cnum;
            scanf("%d %d", &cnum.re, &cnum.im);
            tr1.search(&tr1, tr1.defnode, &cnum);
        }
        else
        {
            int num;
            printf("\nЗначение\n");
            scanf("%d", &num);
            tr1.search(&tr1, tr1.defnode, &num);
        }
        tr1.free_tree(tr1.defnode);
    }
    if(mode == 4)
    {
        tree tr1, tr2;
        tr1.init();
        tr2.init();
        tr1.get_type();
        printf("Дерево 1\n");
        tr1.fill_tree(&tr1);
        printf("Представление дерева 1\n");
        tr1.traverse(&tr1, tr1.defnode, 0);
        tr2.type = tr1.type;
        printf("\nДерево 2, потенциальное поддерево\n");
        tr2.fill_tree(&tr2);
        printf("Представление дерева 2\n");
        tr2.traverse(&tr2, tr2.defnode, 0);
        if(tr2.check_subtree(&tr1))
            printf("\nДерево 2 является поддеревом дерева 1\n");
        else
            printf("\nДерево 2 не является поддеревом дерева 1.\n");
        tr1.free_tree(tr1.defnode);
        tr2.free_tree(tr2.defnode);
    }
    if(mode == 5)
    {
        tree tr1, tr2;
        tr1.init();
        tr2.init();
        tr1.get_type();
        printf("Дерево 1\n");
        tr1.fill_tree(&tr1);
        printf("Представление дерева 1\n");
        tr1.traverse(&tr1, tr1.defnode, 0);
        tr2.type = tr1.type;
        printf("\nДерево 2, потенциальное поддерево\n");
        tr2.fill_tree(&tr2);
        printf("Представление дерева 2\n");
        tr2.traverse(&tr2, tr2.defnode, 0);
        tree** arr_trees = new tree*[2];
        arr_trees[0] = &tr1;
        arr_trees[1] = &tr2;
        printf("\nВыберите функцию для отображения деревьев:\n");
        printf("1. Добавьте одно\n");
        printf("2. Вычесть одно\n");
        void (*foo)(tree*, tree::node*);
        int func;
        scanf("%d", &func);
        func--;
        if(func)
            foo = &subone;
        else
            foo = &addone;
        map(arr_trees, 2, foo);
        printf("\nОтображение нового дерева 1:\n");
        tr1.traverse(&tr1, tr1.defnode, 0);
        printf("\nОтображение нового дерева 2:\n");
        tr2.traverse(&tr2, tr2.defnode, 0);
        tr1.free_tree(tr1.defnode);
        tr2.free_tree(tr2.defnode);
        delete arr_trees;
    }
    if(mode == 6)
    {
        tree tr1, tr2;
        tr1.init();
        tr2.init();
        tr1.get_type();
        tr1.fill_tree(&tr1);
        printf("Представление дерева\n");
        tr1.traverse(&tr1, tr1.defnode, 0);
        tr2.type = tr1.type;
        printf("\nВыберите режим выбора «where»:\n 1. Выберите меньшее\n 2. Выберите больше\n");
        int select;
        scanf("%d", &select);
        select--;
        printf("Выберите базовое значение выбора:\n");
        int condition;
        scanf("%d", &condition);
        wher(&tr2, tr1.defnode, condition, select);
        printf("Представление нового дерева\n");
        tr2.traverse(&tr2, tr2.defnode, 0);
        tr1.free_tree(tr1.defnode);
        tr2.free_tree(tr2.defnode);
    }
    program_exit();
}

int main()
{
    system("chcp 1251");
    system("cls"); //Включает русский язык
    printf("Выберите режим работы\n");
    printf("1. Пользователь\n");
    printf("2. Разработчик\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
        user();
    if (choice == 2)
        test();
    if (choice != 1 && choice != 2)
        program_exit();
    return 0;
}
