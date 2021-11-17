package ft.hangouts.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.text.SimpleDateFormat;

import ft.hangouts.R;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.model.Message;

public class MessageAdapter extends ArrayAdapter<Message> {

    private static final int VIEW_TYPE_MESSAGE_SENT = 0;
    private static final int VIEW_TYPE_MESSAGE_RECEIVED = 1;

    public static final SimpleDateFormat DATE_FORMAT = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    private final DatabaseHelper mDatabaseHelper;
    private final Contact mContact;

    public MessageAdapter(Context context, DatabaseHelper databaseHelper, Contact contact) {
        super(context, 0);

        this.mDatabaseHelper = databaseHelper;
        this.mContact = contact;
    }

    public void refresh() {
        clear();
        addAll(mDatabaseHelper.findAllMessageByContact(mContact));
    }

    @Override
    public int getViewTypeCount() {
        return 2;
    }

    @Override
    public int getItemViewType(int position) {
        if (position >= getCount()) {
            return VIEW_TYPE_MESSAGE_SENT;
        }

        Message message = getItem(position);

        if (message.isSent()) {
            return VIEW_TYPE_MESSAGE_SENT;
        }

        return VIEW_TYPE_MESSAGE_RECEIVED;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        Message message = getItem(position);

        if (convertView == null) {
            int type = getItemViewType(position);
            int layout = getLayoutFor(type);

            convertView = LayoutInflater.from(getContext()).inflate(layout, parent, false);
            convertView.setTag(new ViewHolder(convertView));
        }

        ViewHolder holder = (ViewHolder) convertView.getTag();

        holder.getContentTextView().setText(message.getBody());
        holder.getTimestampTextView().setText(DATE_FORMAT.format(message.getAt()));

        return convertView;
    }

    private int getLayoutFor(int type) {
        switch (type) {
            case VIEW_TYPE_MESSAGE_SENT: {
                return R.layout.row_message_sent;
            }

            case VIEW_TYPE_MESSAGE_RECEIVED: {
                return R.layout.row_message_received;
            }

            default: {
                throw new IllegalStateException(String.valueOf(type));
            }
        }
    }

    public class ViewHolder {

        private TextView mContentTextView;
        private TextView mTimestampTextView;

        public ViewHolder(View itemView) {
            mContentTextView = itemView.findViewById(R.id.content);
            mTimestampTextView = itemView.findViewById(R.id.timestamp);
        }

        public TextView getContentTextView() {
            return mContentTextView;
        }

        public TextView getTimestampTextView() {
            return mTimestampTextView;
        }
    }

}