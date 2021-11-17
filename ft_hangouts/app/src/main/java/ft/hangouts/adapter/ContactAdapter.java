package ft.hangouts.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import ft.hangouts.Constants;
import ft.hangouts.R;
import ft.hangouts.activity.ContactActivity;
import ft.hangouts.activity.ContactsActivity;
import ft.hangouts.activity.MessagesActivity;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;

public class ContactAdapter extends ArrayAdapter<Contact> {

    private final ContactsActivity mContactsActivity;
    private final DatabaseHelper mDatabaseHelper;

    public ContactAdapter(ContactsActivity contactsActivity, DatabaseHelper databaseHelper) {
        super(contactsActivity, 0);

        this.mContactsActivity = contactsActivity;
        this.mDatabaseHelper = databaseHelper;
    }

    public void refresh() {
        clear();
        addAll(mDatabaseHelper.findAllContacts());
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        Contact contact = getItem(position);

        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.row_contact, parent, false);
            convertView.setTag(new ViewHolder(convertView));
        }

        ViewHolder holder = (ViewHolder) convertView.getTag();

        holder.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MessagesActivity.start(mContactsActivity, Constants.REQUEST_CODE_CONTACT_ACTIVITY, contact);
            }
        });

        holder.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                ContactActivity.start(mContactsActivity, Constants.REQUEST_CODE_CONTACT_ACTIVITY, contact, true);
                return true;
            }
        });

        holder.setName(contact.getName());
        holder.setPhone(contact.getPhone());

        return convertView;
    }

    public static class ViewHolder {

        private final View mView;
        private final TextView mNameTextView;
        private final TextView mPhoneTextView;

        public ViewHolder(View view) {
            mView = view;
            mNameTextView = view.findViewById(R.id.name);
            mPhoneTextView = view.findViewById(R.id.phone);
        }

        public void setOnLongClickListener(View.OnLongClickListener listener) {
            mView.setOnLongClickListener(listener);
        }

        public void setOnClickListener(View.OnClickListener listener) {
            mView.setOnClickListener(listener);
        }

        public void setName(String name) {
            if (name != null) {
                name = name.trim();
            } else {
                name = "<???>";
            }

            mNameTextView.setText(name);
        }

        public void setPhone(String phone) {
            if (phone != null) {
                phone = phone.trim();
            } else {
                phone = "+???";
            }

            mPhoneTextView.setText(phone);
        }
    }

}