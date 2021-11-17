package ft.hangouts.model;

import android.content.ContentValues;
import android.database.Cursor;
import android.provider.BaseColumns;

import java.util.Date;

public class Message {

    public static final boolean SIDE_SEND = true;
    public static final boolean SIDE_RECEIVED = false;

    private long id;
    private boolean side;
    private long contactId;
    private String body;
    private Date at;

    public long getId() {
        return id;
    }

    public Message setId(long id) {
        this.id = id;

        return this;
    }

    public boolean isSide() {
        return side;
    }

    public Message setSide(boolean side) {
        this.side = side;

        return this;
    }

    public long getContactId() {
        return contactId;
    }

    public Message setContact(Contact contact) {
        return setContactId(contact.getId());
    }

    public Message setContactId(long contactId) {
        this.contactId = contactId;

        return this;
    }

    public String getBody() {
        return body;
    }

    public Message setBody(String body) {
        this.body = body;

        return this;
    }

    public Date getAt() {
        return at;
    }

    public Message setAt(Date at) {
        this.at = at;

        return this;
    }

    public boolean isSent() {
        return side == SIDE_SEND;
    }

    public boolean isReceived() {
        return side == SIDE_RECEIVED;
    }

    public ContentValues toValues() {
        ContentValues values = new ContentValues();

        values.put(Columns.COLUMN_NAME_SIDE, side ? 1 : 0);
        values.put(Columns.COLUMN_NAME_CONTACT_ID, contactId);
        values.put(Columns.COLUMN_NAME_BODY, body);
        values.put(Columns.COLUMN_NAME_AT, at.getTime());

        return values;
    }

    public static Message fromCursor(Cursor cursor) {
        return new Message()
                .setId(cursor.getLong(cursor.getColumnIndexOrThrow(Columns._ID)))
                .setSide(cursor.getInt(cursor.getColumnIndexOrThrow(Columns.COLUMN_NAME_SIDE)) == 1)
                .setContactId(cursor.getLong(cursor.getColumnIndexOrThrow(Columns.COLUMN_NAME_CONTACT_ID)))
                .setBody(cursor.getString(cursor.getColumnIndexOrThrow(Columns.COLUMN_NAME_BODY)))
                .setAt(new Date(cursor.getLong(cursor.getColumnIndexOrThrow(Columns.COLUMN_NAME_AT))));
    }

    public static class Columns implements BaseColumns {

        public static final String TABLE_NAME = "messages";
        public static final String COLUMN_NAME_SIDE = "side";
        public static final String COLUMN_NAME_CONTACT_ID = "contact_id";
        public static final String COLUMN_NAME_BODY = "body";
        public static final String COLUMN_NAME_AT = "at";

        public static final String SQL_CREATE_ENTRIES =
                "CREATE TABLE " + TABLE_NAME + " (" +
                        _ID + " INTEGER PRIMARY KEY," +
                        COLUMN_NAME_SIDE + " INTEGER," +
                        COLUMN_NAME_CONTACT_ID + " INTEGER REFERENCES " + Contact.Columns.TABLE_NAME + "," +
                        COLUMN_NAME_BODY + " TEXT," +
                        COLUMN_NAME_AT + " INTEGER)";

        public static final String SQL_DELETE_ENTRIES =
                "DROP TABLE IF EXISTS " + TABLE_NAME;

        public static final String[] PROJECTION = {
                _ID,
                COLUMN_NAME_SIDE,
                COLUMN_NAME_CONTACT_ID,
                COLUMN_NAME_BODY,
                COLUMN_NAME_AT,
        };

    }

}