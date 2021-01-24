#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

/* �Եݹ�ķ�ʽ��ӡjson�����ڲ��ֵ�� */
void printJson(cJSON * root)
{
    for(int i=0; i<cJSON_GetArraySize(root); i++)   //���������json��ֵ��
    {
        cJSON * item = cJSON_GetArrayItem(root, i);
        if(cJSON_Object == item->type)      //�����Ӧ����ֵ��ΪcJSON_Object�͵ݹ����printJson
            printJson(item);
        else                                //ֵ��Ϊjson�����ֱ�Ӵ�ӡ������ֵ
        {
            printf("%s->", item->string);
            printf("%s\n", cJSON_Print(item));
        }
    }
}

int main()
{
    char * jsonStr = "{\"semantic\":{\"slots\":{\"name\":\"����\"}}, \"rc\":0, \"operation\":\"CALL\", \"service\":\"telephone\", \"text\":\"��绰������\"}";
    cJSON * root = NULL;
    cJSON * item = NULL;//cjson����

    root = cJSON_Parse(jsonStr);
    if (!root)
    {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }
    else
    {
        printf("%s\n", "�и�ʽ�ķ�ʽ��ӡJson:");
        printf("%s\n\n", cJSON_Print(root));
        printf("%s\n", "�޸�ʽ��ʽ��ӡjson��");
        printf("%s\n\n", cJSON_PrintUnformatted(root));

        printf("%s\n", "һ��һ���Ļ�ȡname ��ֵ��:");
        item = cJSON_GetObjectItem(root, "semantic");//
        printf("�ȴ�ӡ��ǰ������ڵ�����:%s\n", item->string);
        printf("%s\n", "��ȡsemantic�µ�cjson����:");
        printf("%s\n", cJSON_Print(item));
        item = cJSON_GetObjectItem(item, "slots");
        printf("�ȴ�ӡ��ǰ������ڵ�����:%s\n", item->string);
        printf("%s\n", "��ȡslots�µ�cjson����");
        printf("%s\n", cJSON_Print(item));
        printf("%s\n", "��ȡname�µ�cjson����");
        item = cJSON_GetObjectItem(item, "name");
        printf("%s\n", cJSON_Print(item));

        printf("%s:", item->string);   //��һ��cjson����Ľṹ������������Ա����˼
        printf("%s\n", item->valuestring);


        printf("\n%s\n", "��ӡjson�������ڲ��ֵ��:");
        printJson(root);

        //
        cJSON_Delete(root);
    }
    return 0;
}
