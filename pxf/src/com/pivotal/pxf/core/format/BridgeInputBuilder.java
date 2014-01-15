package com.pivotal.pxf.core.format;

import com.pivotal.pxf.api.format.OneField;
import com.pivotal.pxf.api.format.OutputFormat;
import com.pivotal.pxf.api.io.DataType;
import com.pivotal.pxf.api.utilities.InputData;
import com.pivotal.pxf.core.io.GPDBWritable;
import com.pivotal.pxf.core.io.Text;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.io.DataInput;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class BridgeInputBuilder {
    private InputData inputData;
    private static final Log LOG = LogFactory.getLog(BridgeInputBuilder.class);

    public BridgeInputBuilder(InputData inputData) throws Exception {
        this.inputData = inputData;
    }

    public List<OneField> makeOutput(DataInput inputStream) throws Exception {
        if (inputData.outputFormat() == OutputFormat.FORMAT_TEXT) {
            Text txt = new Text();
            txt.readFields(inputStream);
            return Collections.singletonList(new OneField(DataType.BYTEA.getOID(), txt.getBytes()));
        }

        GPDBWritable gpdbWritable = new GPDBWritable();
        gpdbWritable.readFields(inputStream);

        if (gpdbWritable.isEmpty()) {
            LOG.debug("Reached end of stream");
            return null;
        }

        GPDBWritableMapper mapper = new GPDBWritableMapper(gpdbWritable);
        int[] colTypes = gpdbWritable.getColType();
        List<OneField> record = new LinkedList<OneField>();
        for (int i = 0; i < colTypes.length; i++) {
            mapper.setDataType(colTypes[i]);
            record.add(new OneField(colTypes[i], mapper.getData(i)));
        }

        return record;
    }
}