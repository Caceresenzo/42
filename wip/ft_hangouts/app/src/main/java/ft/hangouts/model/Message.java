package ft.hangouts.model;

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

}