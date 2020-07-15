package jk.dev.cryptomessaging.Utilities;

/**
 * Created by the awesome and extraordinary developer Jim on 18/1/2016.
 */


import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.List;

import jk.dev.cryptomessaging.R;

public class MessagesListAdapter extends BaseAdapter {

    private Context context;
    private List<Message> messagesItems;

    public MessagesListAdapter(Context context, List<Message> navDrawerItems) {
        this.context = context;
        this.messagesItems = navDrawerItems;
    }

    @Override
    public int getCount() {
        return messagesItems.size();
    }

    @Override
    public Object getItem(int position) {
        return messagesItems.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    public void addMessage(Message message) {
        messagesItems.add(message);
        notifyDataSetChanged();
    }

    @SuppressLint("InflateParams")
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        /**
         * The following list not implemented reusable list items as list items
         * are showing incorrect data Add the solution if you have one
         * */

        Message m = messagesItems.get(position);

        LayoutInflater mInflater = (LayoutInflater) context
                .getSystemService(Activity.LAYOUT_INFLATER_SERVICE);

        // Identifying the message owner
        if (messagesItems.get(position).isSelf()) {
            // message belongs to you, so load the right aligned layout
            convertView = mInflater.inflate(R.layout.message_right,
                    null);
        } else {
            // message belongs to other person, load the left aligned layout
            convertView = mInflater.inflate(R.layout.message_left,
                    null);
        }


        TextView lblFrom = (TextView) convertView.findViewById(R.id.lblMsgFrom);

        TextView txtMsg = (TextView) convertView.findViewById(R.id.txtMsg);

        if (m.isImage()) {
            txtMsg.setText(" ");
          /*  LayoutParams lp = (RelativeLayout.LayoutParams) tv.getLayoutParams();*/
            txtMsg.setBackground(m.getDrawable());
        } else {
            txtMsg.setText(m.getMessage());
        }
        lblFrom.setText(m.getFromName());

        return convertView;
    }
}