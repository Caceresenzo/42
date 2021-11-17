package ft.hangouts.receiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.telephony.SmsMessage;
import android.widget.Toast;

import java.util.Date;

import ft.hangouts.activity.ContactsActivity;
import ft.hangouts.activity.MessagesActivity;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.model.Message;

public class SMSReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        byte[][] messages = (byte[][]) intent.getExtras().get("pdus");

        for (byte[] message : messages) {
            SmsMessage sms = SmsMessage.createFromPdu(message);

            String address = sms.getOriginatingAddress();
            String body = sms.getMessageBody();

            handleMessage(context, address, body);
            Toast.makeText(context, String.format("%s: %s", address, body), Toast.LENGTH_SHORT).show();
        }
    }

    private Contact createContactIfMissing(DatabaseHelper helper, String address) {
        Contact contact = helper.findContactByPhone(address);
        if (contact == null) {
            contact = new Contact().setPhone(address);
        }

        contact.setLatestUpdate(new Date());

        return helper.save(contact);
    }

    private Message createMessage(DatabaseHelper helper, Contact contact, String body) {
        return helper.save(new Message()
                .setBody(body)
                .setContact(contact)
                .setAt(new Date())
                .setSide(Message.SIDE_RECEIVED));
    }

    private void handleMessage(Context context, String address, String body) {
        DatabaseHelper helper = new DatabaseHelper(context);

        Contact contact = createContactIfMissing(helper, address);
        Message message = createMessage(helper, contact, body);

        if (ContactsActivity.getInstance() != null) {
            ContactsActivity.getInstance().getContactAdapter().refresh();
        }

        if (MessagesActivity.getInstance() != null) {
            MessagesActivity.getInstance().add(message);
        }
    }

}