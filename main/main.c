#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xBinarySemaphore1 = NULL;
SemaphoreHandle_t xBinarySemaphore2 = NULL;
SemaphoreHandle_t xBinarySemaphore3 = NULL;


void Manager(void *pvParameters)
{
    int value = 0;
    int vez = 1;
    while (1) 
    {
        value++;
        if(vez == 1) 
        {
            xSemaphoreGive(xBinarySemaphore1);
            vez = 2;
        } else if (vez == 2)
        {
            xSemaphoreGive(xBinarySemaphore2); 
            vez = 3; 
        } else if ( vez == 3) {
            xSemaphoreGive(xBinarySemaphore3); 
            vez = 1; 
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Tarefa1(void *pvParameters)
{
    while (1) 
    {
        if(xSemaphoreTake(xBinarySemaphore1, portMAX_DELAY) == pdTRUE) 
        {
            printf("[Tarefa 1] Executou - Nathalia \n");
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void Tarefa2(void *pvParameters)
{
    while (1) 
    {
        if(xSemaphoreTake(xBinarySemaphore2, portMAX_DELAY) == pdTRUE) 
        {
            printf("[Tarefa 2] Executou - Nathalia\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void Tarefa3(void *pvParameters)
{
    while (1) 
    {
        if(xSemaphoreTake(xBinarySemaphore3, portMAX_DELAY) == pdTRUE) 
        {
            printf("[Tarefa 3] Executou - Nathalia\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void app_main(void)
{
    xBinarySemaphore1 = xSemaphoreCreateBinary(); 
    xBinarySemaphore2 = xSemaphoreCreateBinary();
    xBinarySemaphore3 = xSemaphoreCreateBinary();    

    if (xBinarySemaphore1 == NULL && xBinarySemaphore2 == NULL  && xBinarySemaphore3 == NULL) 
    {
        printf("Falha ao criar semáforo binário\n");
        return;
    }


    xTaskCreate(Manager,
                "Manager", 
                2048,
                NULL, 
                5, 
                NULL);

    xTaskCreate(Tarefa1,
                "Tarefa1", 
                2048, 
                NULL,
                5, 
                NULL );

    xTaskCreate(Tarefa2,
                "Tarefa2",
                2048,
                NULL, 
                5, 
                NULL );

    xTaskCreate(Tarefa3,
                "Tarefa3",
                2048,
                NULL, 
                5, 
                NULL );

}