package ft.hangouts.model;

import android.content.ContentValues;
import android.provider.BaseColumns;

import java.io.Serializable;

public class Contact implements Serializable {

    private long id;
    private String phone;
    private String name;
    private String nickname;
    private String email;
    private String address;

    public long getId() {
        return id;
    }

    public Contact setId(long id) {
        this.id = id;

        return this;
    }

    public String getPhone() {
        return phone;
    }

    public Contact setPhone(String phone) {
        this.phone = phone;

        return this;
    }

    public String getName() {
        return name;
    }

    public Contact setName(String name) {
        this.name = name;

        return this;
    }

    public String getNickname() {
        return nickname;
    }

    public Contact setNickname(String nickname) {
        this.nickname = nickname;

        return this;
    }

    public String getEmail() {
        return email;
    }

    public Contact setEmail(String email) {
        this.email = email;

        return this;
    }

    public String getAddress() {
        return address;
    }

    public Contact setAddress(String address) {
        this.address = address;

        return this;
    }

    public ContentValues toValues() {
        ContentValues values = new ContentValues();

        values.put(Contact.Columns.COLUMN_NAME_PHONE, phone);
        values.put(Contact.Columns.COLUMN_NAME_NAME, name);
        values.put(Contact.Columns.COLUMN_NAME_NICKNAME, nickname);
        values.put(Contact.Columns.COLUMN_NAME_EMAIL, email);
        values.put(Contact.Columns.COLUMN_NAME_ADDRESS, address);

        return values;
    }

    /* Inner class that defines the table contents */
    public static class Columns implements BaseColumns {

        public static final String TABLE_NAME = "contacts";
        public static final String COLUMN_NAME_PHONE = "phone";
        public static final String COLUMN_NAME_NAME = "name";
        public static final String COLUMN_NAME_NICKNAME = "nickname";
        public static final String COLUMN_NAME_EMAIL = "email";
        public static final String COLUMN_NAME_ADDRESS = "address";

        public static final String SQL_CREATE_ENTRIES =
                "CREATE TABLE " + TABLE_NAME + " (" +
                        _ID + " INTEGER PRIMARY KEY," +
                        COLUMN_NAME_PHONE + " TEXT," +
                        COLUMN_NAME_NAME + " TEXT," +
                        COLUMN_NAME_NICKNAME + " TEXT," +
                        COLUMN_NAME_EMAIL + " TEXT," +
                        COLUMN_NAME_ADDRESS + " TEXT)";

        public static final String SQL_DELETE_ENTRIES =
                "DROP TABLE IF EXISTS " + TABLE_NAME;

        public static final String[] PROJECTION = {
                _ID,
                COLUMN_NAME_PHONE,
                COLUMN_NAME_NAME,
                COLUMN_NAME_NICKNAME,
                COLUMN_NAME_EMAIL,
                COLUMN_NAME_ADDRESS,
        };

    }

}