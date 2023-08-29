1. 通过多个字段清除重复的数据

```sql
DELETE FROM (SELECT COIL_ID,UNQUAL_SOURCE,UNQUAL_CATEGORY,ROW_NUMBER() OVER(PARTITION BY COIL_ID,UNQUAL_CATEGORY,UNQUAL_SOURCE ORDER BY COIL_ID) AS RN, a.* FROM TEST a) WHERE rn >1;
```

1. 拼接字符串

```sql
select
  COIL_ID,
  LISTAGG('['||UNQUAL_SOURCE||']' || UNQUAL_VALUE, ', ') WITHIN GROUP(ORDER BY UNQUAL_VALUE ASC) as UNQUAL_VALUE
from UNQUAL_HISTORY
group by COIL_ID,UNQUAL_CATEGORY;
```

3. ### 取第一条数据

```sql
select 
	L3_SLAB_ID,ACT_SLAB_ID,INSP_IND
from
	H421.DC_HSM1_PDI
where
	ACT_SLAB_ID = '1232323'
order by toc desc fetch first 1 rows only
```

4. ### db2 - 基于 db2 中的 ID 匹配，从一个表到另一个表的 SQL 更新

```sql
UPDATE
     Sales_Import SI
 SET
    Sales_Import.AccountNumber = (
      SELECT 
        RAN.AccountNumber
      FROM
        RetrieveAccountNumber RAN
      WHERE  
        SI.LeadID = RAN.LeadID
    )
```
