#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int id;
    char *name;
    float price;
}product;

typedef struct{
    product **products;
    int current_size;
    int max;
}list_products;

typedef struct{
    int current_size;
    int size_max;
    product **products;
    float priceTotal;
}list;

typedef struct{
    char *name;
    list *l;
}client;

typedef struct{
    int size_max;
    int current_size;
    client **clients;
}client_list;

list_products *createList_Products(int max)
{
    list_products *lp = (list_products*)malloc(sizeof(list_products));
    lp->products = (product**)malloc(max * sizeof(product*));
    lp->max = max;
    lp->current_size = 0;

    return lp;
}

product *createProduct(char *name_prod, float price, int id)
{
    product *p = (product*)malloc(sizeof(product));
    p->name = (char*)malloc(strlen(name_prod) + 1);
    strcpy(p->name, name_prod);
    
    p->id = id;
    p->price = price;

    return p;
}

list *createList_client(int max_size)
{
    list *l = (list*)malloc(sizeof(list));
    l->products = (product**)malloc(max_size * sizeof(product*));
    l->current_size = 0;
    l->priceTotal = 0;
    l->size_max = max_size;

    return l;
}

client *createClient(char *name_client) 
{
    client* c = (client*)malloc(sizeof(client));
    c->name = (char*)malloc(strlen(name_client) + 1);
    strcpy(c->name, name_client);

    c->l = createList_client(10);

    return c;
}

client_list *createClient_List(int max_size)
{
    client_list *cl = (client_list*)malloc(sizeof(client_list));
    cl->clients = (client**)malloc(max_size * sizeof(client*));
    cl->size_max = max_size;
    cl->current_size = 0;

    return cl;
}

void addClientToClientList(client_list *cl, client *c)
{
    if(cl->current_size < cl->size_max)
    {
        cl->clients[cl->current_size] = c;
        cl->current_size++;
    }
    else
    {
        printf("Client List are full!\n");
    }
}

void addProdToList(client *c, product *p)
{   
    if(c->l->current_size < c->l->size_max)
    {
        c->l->products[c->l->current_size] = p;
        c->l->priceTotal += p->price;
        c->l->current_size++;
    }
    else
    {
        printf("Products List are full!\n");
    }
}

void addProdToGeneralList(list_products *lp, product *p)
{
    if(lp->current_size < lp->max)
    {
        lp->products[lp->current_size] = p;
        lp->current_size++;
    }
    else{
        printf("General Products List are full!\n");
    }
}

int menu_system_design()
{
    int choice;
    printf("\33[H\33[2J");
    printf("************************************************");
    printf("        system      ");
    printf("************************************************\n\n");

    printf("1 - Client\n");
    printf("2 - Products\n");

    printf("What u want: ");
    scanf("%d", &choice);

    return choice;
}

int menu_client_design(client_list *cl)
{
    int choice;

    printf("\33[H\33[2J");
    printf("************************************************");
    printf("        client      ");
    printf("************************************************\n\n");

    if(cl->current_size == 0)
    {
        printf("Don't have clients yet\n");
    }
    else
    {
        for(int i = 0; i < cl->current_size; i++)
        {
            printf("%d - Client : %s\n", i, cl->clients[i]->name);
        }
    }
    
    printf("\nx - Choose client number\n");
    printf("10 - Create Client\n");
    printf("11 - Return to menu\n");

    printf("What u want: ");
    scanf("%d", &choice);

    return choice;
}

void menu_create_client(client_list *cl)
{
    char name[30];

    printf("\33[H\33[2J");  
    printf("Client name: ");
    scanf("%s", name);

    client *c = createClient(name);

    addClientToClientList(cl, c);
}

int menu_client_choice(int client_number, client_list *cl)
{
    int choice;

    printf("\33[H\33[2J");
    printf("************************************************");
    printf("        client      ");
    printf("************************************************\n\n");

    if(cl->clients[client_number]->l->current_size == 0)
    {
        printf("%s don't have products yet\n",cl->clients[client_number]->name);
    }
    else
    {
        for(int i = 0; i < cl->clients[client_number]->l->current_size; i++)
        {
            printf("%d - %s : %.2f\n", i, 
                               cl->clients[client_number]->l->products[i]->name, 
                             cl->clients[client_number]->l->products[i]->price);
        }
    }


    printf("\nTotal price to pay: %.2f\n", 
                                     cl->clients[client_number]->l->priceTotal);
    printf("\n1 - Add Product\n");
    printf("2 - Remove Product\n");
    printf("3 - Return to menu\n");

    printf("What u want %s: ", cl->clients[client_number]->name);
    scanf("%d", &choice);

    return choice;
}

void menu_client_products_add(int client_number, client_list *cl, 
                                                              list_products *lp)
{
    int choice;
    int quantity;

    printf("\33[H\33[2J");
    printf("************************************************");
    printf("        list product client add    ");
    printf("************************************************\n\n");

    if(lp->current_size == 0)
    {
        printf("Don't have products yet\n");
    }
    else
    {
        for(int i = 0; i < lp->current_size; i++)
        {
            printf("%d - %s : %.2f\n", i, lp->products[i]->name, 
                                                        lp->products[i]->price);
        }
    }

    printf("\nx - Add product to client list\n");
    printf("10 - Return to Menu\n");

    printf("What u want %s: ", cl->clients[client_number]->name);
    scanf("%d", &choice);

    if(choice >= 0 && choice < cl->clients[client_number]->l->size_max)
    {
        printf("\nHow many %s u want: \n", lp->products[choice]->name);
        scanf("%d", &quantity);

        for(int j = 0; j < quantity; j++)
        {
            addProdToList(cl->clients[client_number], lp->products[choice]);
        }
    }
}

int menu_products_list(list_products *lp)
{
    printf("\33[H\33[2J");  
    printf("************************************************");
    printf("        products general list     ");
    printf("************************************************\n\n");

    if(lp->products[0] != NULL)
    {
        for(int i = 0; i < lp->current_size; i++)
        {
            if(lp->products[i] != NULL)
            {
                printf("id: %d - %s -> R$%.2f\n", lp->products[i]->id, 
                                 lp->products[i]->name, lp->products[i]->price);
            }else
            {
                break;
            }
        }    
    }
    else{
        printf("Don't have products yet\n");
    }
      
    int choice;
    printf("\n1 - Create Product\n");
    printf("2 - Remove a product\n");
    printf("3 - Back to Menu\n");

    printf("What u want: ");
    scanf("%d", &choice);

    return choice;        
}

void remove_product_client_list(int client_number, client_list *cl)
{
    int choice;
    float aux;

    printf("\33[H\33[2J");  
    printf("************************************************");
    printf("     remove product client list   ");
    printf("************************************************\n\n");

    if(cl->clients[client_number]->l->current_size == 0)
    {
        printf("%s don't have products yet\n",cl->clients[client_number]->name);
    }
    else
    {
        for(int i = 0; i < cl->clients[client_number]->l->current_size; i++)
        {
            printf("%d - %s : %.2f\n", i, 
                               cl->clients[client_number]->l->products[i]->name, 
                             cl->clients[client_number]->l->products[i]->price);
        }
    }

    printf("\nChoose number of the product which u want to remove: \n");
    scanf("%d", &choice);

    aux = cl->clients[client_number]->l->products[choice]->price;
    for(int j = choice; j < cl->clients[client_number]->l->current_size; j++)
    {
        cl->clients[client_number]->l->products[j] = 
                                 cl->clients[client_number]->l->products[j + 1];
    }

    list *l_temp = realloc(cl->clients[client_number]->l, sizeof(list));
    if(l_temp == NULL && l_temp->current_size > 1)
    {
        exit(EXIT_FAILURE);
    }

    cl->clients[client_number]->l->current_size = 
                                cl->clients[client_number]->l->current_size - 1;
    cl->clients[client_number]->l = l_temp;
    cl->clients[client_number]->l->priceTotal -= aux;
}

void remove_product_general_list(list_products *lp)
{
    int choice;

    printf("\33[H\33[2J");  
    printf("************************************************");
    printf("     remove product general list   ");
    printf("************************************************\n\n");

    if(lp->current_size == 0)
    {
        printf("Don't have products yet\n");
    }
    else
    {
        for(int i = 0; i < lp->current_size; i++)
        {
            printf("%d - %s : %.2f\n", i, lp->products[i]->name, 
                                                        lp->products[i]->price);
        }
    }

    printf("\nChoose number of the product which u want to remove: \n");
    scanf("%d", &choice);

    for(int j = choice; j < lp->current_size; j++)
    {
        lp->products[j] = lp->products[j+1];
    }

    list_products *lp_temp = realloc(lp, sizeof(list_products));
    if(lp_temp == NULL && lp_temp->current_size > 1)
    {
        exit(EXIT_FAILURE);
    }

    lp->current_size = lp->current_size - 1;
    lp = lp_temp;
}

void menu_create_product(list_products *lp)
{
    char nome[30];
    float preco;
    int id  = lp->current_size;
    
    printf("\33[H\33[2J");  
    printf("************************************************");
    printf("        create product     ");
    printf("************************************************\n\n");

    printf("Product Id: %d\n", id);

    printf("Which name of product: ");
    scanf("%s", nome);

    printf("How much this product will costs: ");
    scanf("%f", &preco);
    
    product *produto = createProduct(nome, preco, id);

    addProdToGeneralList(lp, produto);
}
int main()
{
    client_list *cl = createClient_List(10);
    list_products *general_list = createList_Products(10);
    int chosen, chosenClient, chosenClient2, chosenListProducts;
    
    while(1)
    { 
        chosen = menu_system_design(); 
        do
        {
            switch (chosen)
            {
            case 1:
                chosenClient = menu_client_design(cl);
                
                if(chosenClient < cl->size_max)
                {
                    chosenClient2 = menu_client_choice(chosenClient, cl);

                    switch (chosenClient2)
                    {
                    case 1:
                        menu_client_products_add(chosenClient, cl,general_list);
                        break;
                    
                    case 2:
                        remove_product_client_list(chosenClient, cl);
                        break;

                    default:
                        break;
                    }
                    break;
                }
                else if (chosenClient == 10) 
                {
                    menu_create_client(cl);
                    break;
                }
                else {
                    break;
                }
                break;
            
            case 2:
                chosenListProducts = menu_products_list(general_list);

                switch (chosenListProducts)
                {
                case 1:
                    menu_create_product(general_list);
                    break;
                
                case 2:
                    remove_product_general_list(general_list);
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
            break;
        } while (chosen != 0 || chosen > 2);
    }

    free(general_list);
    free(cl);

    return 0;  
}