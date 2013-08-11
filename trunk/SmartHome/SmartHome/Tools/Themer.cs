﻿using SmartHome.Network;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SmartHome.Tools
{
    class Themer
    {
        public List<Theme> Themes { get; set; }
    }

    public class Theme
    {
        [Key]
        public int Id { get; set; }

        public string Name { get; set; }

        public List<Operation> Operations { get; set; }
    }


}