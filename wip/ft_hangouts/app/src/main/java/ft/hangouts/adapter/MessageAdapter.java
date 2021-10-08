package ft.hangouts.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

import ft.hangouts.R;
import ft.hangouts.activity.MainActivity;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.model.Message;

public class MessageAdapter extends RecyclerView.Adapter<MessageAdapter.ViewHolder> {

    private static final int VIEW_TYPE_MESSAGE_SENT = 1;
    private static final int VIEW_TYPE_MESSAGE_RECEIVED = 2;

    public static final SimpleDateFormat DATE_FORMAT = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    private final DatabaseHelper mDatabaseHelper;
    private final Contact mContact;
    private List<Message> mMessages;

    public MessageAdapter(DatabaseHelper databaseHelper, Contact contact) {
        this.mDatabaseHelper = databaseHelper;
        this.mContact = contact;
    }

    @Override
    public int getItemViewType(int position) {
        Message message = mMessages.get(position);

        if (message.isSent()) {
            return VIEW_TYPE_MESSAGE_SENT;
        }

        return VIEW_TYPE_MESSAGE_RECEIVED;
    }

    @NonNull
    @Override
    public MessageAdapter.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        int layout;

        switch (viewType) {
            case VIEW_TYPE_MESSAGE_SENT: {
                layout = R.layout.row_message_sent;

                break;
            }

            case VIEW_TYPE_MESSAGE_RECEIVED: {
                layout = R.layout.row_message_received;

                break;
            }

            default: {
                throw new IllegalStateException("viewType: " + viewType);
            }
        }

        View view = LayoutInflater.from(parent.getContext()).inflate(layout, parent, false);

        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull MessageAdapter.ViewHolder holder, int position) {
        Message message = mMessages.get(position);

        holder.getContentTextView().setText(message.getBody());
        holder.getTimestampTextView().setText(DATE_FORMAT.format(message.getAt()));
    }

    @Override
    public int getItemCount() {
        return mMessages.size();
    }

    public void refresh() {
        mMessages = mDatabaseHelper.findAllMessageByContact(mContact);

        notifyDataSetChanged();
    }

    public void add(Message message) {
        mMessages.add(message);

        notifyItemInserted(mMessages.size() - 1);
    }

    public class ViewHolder extends RecyclerView.ViewHolder {

        private TextView mContentTextView;
        private TextView mTimestampTextView;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);

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