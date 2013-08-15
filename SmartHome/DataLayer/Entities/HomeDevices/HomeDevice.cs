﻿#region Using Statements
using DataLayer.Entities.Enums;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
#endregion

namespace DataLayer.Entities.HomeDevices
{
    public abstract class HomeDevice
    {
        [Key]
        [Range(0, 0xFFFF)]
        public int Id { get; set; }

        public string Name { get; set; }

        public Connector Connector { get; set; }

        public ConnectorTypes ConnectorCapable { get; set; }

        public virtual ICollection<Location> Location { get; set; }

        [InverseProperty("SourceHomeDevice")]
        public virtual ICollection<Operation> Operations { get; set; }

        /// <summary>
        /// When is not empty, indicates the location of this HomeDevice in the product.
        /// </summary>
        public ICollection<int> ProductTag { get; set; }

        private static string[] homeDeviceTypes = null;

        //Properties
        [NotMapped]
        public static string[] HomeDeviceTypes
        {
            get
            {
                if (homeDeviceTypes == null)
                    homeDeviceTypes = typeof(HomeDevice).Assembly.GetTypes().Where(t => t != typeof(HomeDevice) && typeof(HomeDevice).IsAssignableFrom(t)).Select(t => t.Name).ToArray();

                return homeDeviceTypes;
            }
        }

        [NotMapped]
        public string HomeDeviceType
        {
            get
            {
                return this.GetType().Name;
            }
        }

        [NotMapped]
        public bool InUse
        {
            get
            {
                return Connector != null;
            }
        }

        public HomeDevice() 
        {
            this.Location = new List<Location>();
            this.Operations = new List<Operation>();
            this.ProductTag = new List<int>();
        }


    }
}