﻿#region Using Statements
using SmartHome.Communications.Messages;
using System.Collections.Generic;
#endregion

namespace SerialPortManager.ConnectionManager
{
    public class OutputHeader
    {
        #region Properties
        public bool SecurityEnabled { get; set; }

        public bool RoutingEnabled { get; set; }

        public int MessageId { get; set; }

        public int EndPoint { get; set; }

        public int Retries { get; set; }

        public IMessage Content { get; set; }

        public float Priority { get; private set; }
        #endregion

        public OutputHeader(float priority = 0)
        {
            if (priority > 1)
                this.Priority = 1;
            else
                this.Priority = priority;
        }

        public byte[] ToBinary()
        {
            List<byte> result = new List<byte>();

            byte headerByte = 0;

            if (SecurityEnabled)
                headerByte |= 0x80;

            if (RoutingEnabled)
                headerByte |= 0x40;

            headerByte |= (byte)(EndPoint & 0x0F);

            result.Add((byte)MessageId);

            result.Add(headerByte);

            result.Add((byte)Retries);

            if (Content != null)
                result.AddRange(Content.ToBinary());

            return result.ToArray();
        }

        public void FromBinary(byte[] buffer)
        {
            MessageId = buffer[0];

            SecurityEnabled = (buffer[1] & 0x80) != 0;

            RoutingEnabled = (buffer[1] & 0x40) != 0;

            EndPoint = (buffer[1] & 0x0F);

            Retries = buffer[2];

            if (Content != null)
                Content.FromBinary(buffer, 3);
        }
    }
}
