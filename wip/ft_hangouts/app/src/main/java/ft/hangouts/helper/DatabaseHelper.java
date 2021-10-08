package ft.hangouts.helper;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.provider.BaseColumns;

import java.util.ArrayList;
import java.util.List;

import ft.hangouts.model.Contact;

public class DatabaseHelper extends SQLiteOpenHelper {

    public static final int DATABASE_VERSION = 1;
    public static final String DATABASE_NAME = "storage.db";

    public static final String WHERE_ID = BaseColumns._ID + " = ?";

    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    public void onCreate(SQLiteDatabase db) {
        db.execSQL(Contact.Columns.SQL_CREATE_ENTRIES);
    }

    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL(Contact.Columns.SQL_DELETE_ENTRIES);
        onCreate(db);
    }

    public void onDowngrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        onUpgrade(db, oldVersion, newVersion);
    }

    public List<Contact> findAllContacts() {
        SQLiteDatabase db = getWritableDatabase();

        try(Cursor cursor = db.query(
                Contact.Columns.TABLE_NAME,
                Contact.Columns.PROJECTION,
                null,
                null,
                null,
                null,
                Contact.Columns.COLUMN_NAME_LATEST_UPDATE + " DESC"
        )) {
            List<Contact> contacts = new ArrayList<>();

            while(cursor.moveToNext()) {
                contacts.add(Contact.fromCursor(cursor));
            }

            return contacts;
        }
    }

    public Contact findContactByPhone(String phone) {
        SQLiteDatabase db = getWritableDatabase();

        try(Cursor cursor = db.query(
                Contact.Columns.TABLE_NAME,
                Contact.Columns.PROJECTION,
                "phone = ?",
                new String[] { phone },
                null,
                null,
                null
        )) {
            if (cursor.moveToNext()) {
                return Contact.fromCursor(cursor);
            }

            return null;
        }
    }

    public Contact save(Contact contact) {
        ContentValues values = contact.toValues();

        if (contact.getId() == 0) {
            long id = insert(Contact.Columns.TABLE_NAME, values);
            contact.setId(id);
        } else {
            update(Contact.Columns.TABLE_NAME, values, contact.getId());
        }

        return contact;
    }

    public void delete(Contact contact) {
        delete(Contact.Columns.TABLE_NAME, contact.getId());
    }

    private long insert(String table, ContentValues values) {
        SQLiteDatabase db = getWritableDatabase();

        return db.insert(table, null, values);
    }

    private long update(String table, ContentValues values, long id) {
        SQLiteDatabase db = getWritableDatabase();

        return db.update(table, values, WHERE_ID, whereId(id));
    }

    public void delete(String table, long id) {
        SQLiteDatabase db = getWritableDatabase();

        db.delete(table, WHERE_ID, whereId(id));
    }

    private String[] whereId(long id) {
        return new String[]{ String.valueOf(id) };
    }

}