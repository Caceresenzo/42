package ft.hangouts.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

import ft.hangouts.R;
import ft.hangouts.activity.ContactActivity;
import ft.hangouts.activity.ContactsActivity;
import ft.hangouts.activity.MessagesActivity;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;

public class ContactAdapter extends RecyclerView.Adapter<ContactAdapter.ViewHolder> {

    private final DatabaseHelper mDatabaseHelper;
    private final ContactsActivity mContactsActivity;
    private List<Contact> mContacts;

    public ContactAdapter(DatabaseHelper databaseHelper, ContactsActivity contactsActivity) {
        this.mDatabaseHelper = databaseHelper;
        this.mContactsActivity = contactsActivity;
    }

    public void refresh() {
        this.mContacts = mDatabaseHelper.findAllContacts();

        notifyDataSetChanged();
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup viewGroup, int viewType) {
        View view = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.row_contact, viewGroup, false);

        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(ViewHolder viewHolder, final int position) {
        Contact contact = mContacts.get(position);

        viewHolder.setName(contact.getName());
        viewHolder.setPhone(contact.getPhone());

        viewHolder.getView().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MessagesActivity.start(mContactsActivity, ContactsActivity.REQUEST_CODE_CONTACT_EDITOR, contact);
            }
        });

        viewHolder.getView().setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                ContactActivity.start(mContactsActivity, ContactsActivity.REQUEST_CODE_CONTACT_EDITOR, contact, true);

                return true;
            }
        });
    }

    @Override
    public int getItemCount() {
        return mContacts.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {

        private final View mView;
        private final TextView mNameTextView;
        private final TextView mPhoneTextView;

        public ViewHolder(View view) {
            super(view);

            mView = view;
            mNameTextView = view.findViewById(R.id.name);
            mPhoneTextView = view.findViewById(R.id.phone);
        }

        public View getView() {
            return mView;
        }

        public TextView getNameTextView() {
            return mNameTextView;
        }

        public TextView getPhoneTextView() {
            return mPhoneTextView;
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